import os
from promote import InternalPromotion, PublicPromotion, PromotionType, Version


def test_internal_major_promotion_bump_version():
    promotion = InternalPromotion(PromotionType.MAJOR)
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
    promotion = InternalPromotion(PromotionType.MINOR)
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
    promotion = InternalPromotion(PromotionType.MINOR)
    assert(promotion.can_publish_release(Version(1, 1, 95)))
    assert(promotion.can_publish_release(Version(1, 1, 90)))
    assert(promotion.can_publish_release(Version(1, 1, 99)))
    assert(not promotion.can_publish_release(Version(1, 1, 50)))


def test_public_major_promotion_bump_version():
    promotion = PublicPromotion(PromotionType.MAJOR)
    assert(promotion.bump_version(Version(1, 1, 5)) == Version(2, 0, 0))


def test_public_minor_promotion_bump_version():
    promotion = PublicPromotion(PromotionType.MINOR)
    assert(promotion.bump_version(Version(1, 1, 1)) == Version(1, 2, 0))


def test_public_patch_promotion_bump_version():
    promotion = PublicPromotion(PromotionType.BUG_FIX)
    assert(promotion.bump_version(Version(1, 1, 1)) == Version(1, 1, 2))


def main():
    while 'scripts' in os.getcwd():
        os.chdir('..')
    test_internal_major_promotion_bump_version()
    test_internal_minor_promotion_bump_version()
    test_internal_minor_promotion_can_publish()
    test_public_major_promotion_bump_version()
    test_public_minor_promotion_bump_version()
    test_public_patch_promotion_bump_version()
    print('All tests passed...')


if __name__ == '__main__':
    main()