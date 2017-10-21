import os
import re
import subprocess
from enum import Enum


class Type(Enum):
    MAJOR = 0
    MINOR = 1
    BUG_FIX = 2


class Version:
    def __init__(self, major=0, minor=0, patch=0):
        self.major = major
        self.minor = minor
        self.patch = patch

    def __str__(self):
        return '%s.%s.%s' % (self.major, self.minor, self.patch)

    def __eq__(self, other):
        return self.major == other.major and self.minor == other.minor and self.patch == other.patch


class Promotion:
    def __init__(self, promotion_type, required_branch, prerelease=False):
        self.prerelease = prerelease
        self.required_branch = required_branch
        self.initial_version = self.read_cmake_version()
        self.new_version = None
        self.promotion_type = promotion_type

    def execute(self):
        self.new_version = self.read_cmake_version()
        self.new_version = self.bump_version(self.initial_version)
        print('Promoting v%s to v%s' % (self.initial_version, self.new_version))
        self.write_cmake_version(self.new_version)

        if self.can_publish_release(self.new_version):
            self.update_change_log()
            self.pull_translations()

            input("check cmake changes and updated changelog and press ENTER if everything is OK")

    def update_change_log(self):
        print('Updating Changelog...')
        changelog_generator_cfg = '.github_changelog_generator'
        with open(changelog_generator_cfg) as f:
            lines = f.read().splitlines()
        updated_lines = []
        for l in lines:
            if l.startswith('future-release='):
                updated_lines.append('future-release=%s' % self.new_version)
            else:
                updated_lines.append(l)
        with open(changelog_generator_cfg, 'w') as f:
            f.write('\n'.join(updated_lines))
        subprocess.check_call(['github_changelog_generator'])

    @staticmethod
    def pull_translations():
        print("Updating translations...")
        subprocess.check_call(['tx', 'pull', '-a'])

    def can_publish_release(self, version):
        raise NotImplementedError()

    def bump_version(self, *args):
        raise NotImplementedError()

    @staticmethod
    def read_cmake_version():
        with open("CMakeLists.txt") as f:
            lines = f.read().splitlines()
        for l in lines:
            if l.startswith("project(MellowPlayer VERSION "):
                m = re.match(r'project\(.*VERSION\s(.*)\.\$.*\)', l)
                if m:
                    version = m.groups()[0]
                    version_numbers = []
                    for n in version.split('.'):
                        version_numbers.append(int(n))
                    return Version(version_numbers[0], version_numbers[1], version_numbers[2])

        return Version()

    @staticmethod
    def write_cmake_version(version):
        with open("CMakeLists.txt") as f:
            lines = f.read().splitlines()
        updated_lines = []
        for l in lines:
            if l.startswith("project(MellowPlayer VERSION "):
                updated_lines.append("project(MellowPlayer VERSION %s.${BUILD_NUMBER})" % version)
            else:
                updated_lines.append(l)

        with open('CMakeLists.txt', 'w') as f:
            f.write('\n'.join(updated_lines))


class PublicPromotion(Promotion):
    def __init__(self, promotion_type):
        super().__init__(promotion_type, 'develop' if promotion_type != Type.BUG_FIX else 'master')

    def bump_version(self, version):
        new_version = Version()
        if self.promotion_type == Type.MAJOR:
            new_version.patch = 0
            new_version.minor = 0
            new_version.major = version.major + 1
        elif self.promotion_type == Type.MINOR:
            new_version.patch = 0
            new_version.minor = version.minor + 1
            new_version.major = version.major
        else:
            new_version.patch = version.patch + 1
            new_version.minor = version.minor
            new_version.major = version.major

        return new_version

    @staticmethod
    def can_publish_release(*args):
        return True


class InternalPromotion(Promotion):
    def __init__(self, promotion_type):
        super().__init__(promotion_type, "develop", prerelease=True)
        self.START_OF_DEVELOPMENT = 50
        self.ALPHA = 90
        self.BETA = 95
        self.RELEASE_CANDIDATE = 99

    def bump_version(self, version):
        new_version = Version()
        if self.promotion_type == Type.MAJOR:
            new_version.patch = 0
            new_version.minor = self.increment_version_number(version.minor)
            new_version.major = version.major
        else:
            new_version.patch = self.increment_version_number(version.patch)
            new_version.minor = version.minor
            new_version.major = version.major

        return new_version

    def increment_version_number(self, version_number):
        if version_number < self.START_OF_DEVELOPMENT:
            return self.START_OF_DEVELOPMENT
        elif version_number == self.START_OF_DEVELOPMENT:
            return self.ALPHA
        elif version_number == self.ALPHA:
            return self.BETA
        elif version_number == self.BETA:
            return self.RELEASE_CANDIDATE
        else:
            raise ValueError('cannot perform internal promotion on a version >= 99, a public promotion is required')

    def can_publish_release(self, version):
        return version.patch != self.START_OF_DEVELOPMENT and version.minor != self.START_OF_DEVELOPMENT


def main(promotion_class, promotion_type):
    while 'scripts' in os.getcwd():
        os.chdir('..')

    promotion = promotion_class(promotion_type)
    promotion.execute()


def public_promotion(promotion_type):
    main(PublicPromotion, promotion_type)


def internal_promotion(promotion_type):
    main(InternalPromotion, promotion_type)


def test_internal_major_promotion_bump_version():
    promotion = InternalPromotion(Type.MAJOR)
    assert(promotion.bump_version(Version(1, 1, 0)) == Version(1, 50, 0))
    assert(promotion.bump_version(Version(1, 1, 15)) == Version(1, 50, 0))
    assert(promotion.bump_version(Version(1, 50, 0)) == Version(1, 90, 0))
    assert(promotion.bump_version(Version(1, 90, 0)) == Version(1, 95, 0))
    assert(promotion.bump_version(Version(1, 95, 0)) == Version(1, 99, 0))
    try:
        promotion.bump_version(Version(1, 99, 0))
    except ValueError as e:
        assert(e is not None)


def test_internal_minor_promotion_bump_version():
    promotion = InternalPromotion(Type.MINOR)
    assert(promotion.bump_version(Version(1, 1, 0)) == Version(1, 1, 50))
    assert(promotion.bump_version(Version(1, 1, 15)) == Version(1, 1, 50))
    assert(promotion.bump_version(Version(1, 1, 50)) == Version(1, 1, 90))
    assert(promotion.bump_version(Version(1, 1, 90)) == Version(1, 1, 95))
    assert(promotion.bump_version(Version(1, 1, 95)) == Version(1, 1, 99))
    try:
        promotion.bump_version(Version(1, 1, 99))
    except ValueError as e:
        assert(e is not None)


def test_internal_minor_promotion_can_publish():
    promotion = InternalPromotion(Type.MINOR)
    assert(promotion.can_publish_release(Version(1, 1, 95)))
    assert(promotion.can_publish_release(Version(1, 1, 90)))
    assert(promotion.can_publish_release(Version(1, 1, 99)))
    assert(not promotion.can_publish_release(Version(1, 1, 50)))


def test_public_major_promotion_bump_version():
    promotion = PublicPromotion(Type.MAJOR)
    assert(promotion.bump_version(Version(1, 1, 5)) == Version(2, 0, 0))


def test_public_minor_promotion_bump_version():
    promotion = PublicPromotion(Type.MINOR)
    assert(promotion.bump_version(Version(1, 1, 1)) == Version(1, 2, 0))


def test_public_patch_promotion_bump_version():
    promotion = PublicPromotion(Type.BUG_FIX)
    assert(promotion.bump_version(Version(1, 1, 1)) == Version(1, 1, 2))

if __name__ == '__main__':
    while 'scripts' in os.getcwd():
        os.chdir('..')

    test_internal_major_promotion_bump_version()
    test_internal_minor_promotion_bump_version()
    test_internal_minor_promotion_can_publish()
    test_public_major_promotion_bump_version()
    test_public_minor_promotion_bump_version()
    test_public_patch_promotion_bump_version()
    print('All tests passed...')