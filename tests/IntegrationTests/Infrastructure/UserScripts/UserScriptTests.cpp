#include <catch/catch.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScript.hpp>
#include <QtCore/QDir>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("UserScriptDirectoryTests")
{
    GIVEN("a UserScriptDirectory instance")
    {
        UserScriptDirectory directory;
        QDir dir(FileHelper::userScriptsDirectory());
        dir.removeRecursively();
        REQUIRE(!dir.exists());

        WHEN("get path")
        {
            auto path = directory.path();

            THEN("path is not empty")
            {
                REQUIRE(!path.isEmpty());
            }
        }

        WHEN("create directory")
        {
            directory.create();

            THEN("directory exists")
            {
                REQUIRE(QDir().exists(directory.path()));
            }
        }

        WHEN("generating two file name")
        {
            auto fileName1 = directory.generateFileName();
            auto fileName2 = directory.generateFileName();

            THEN("they are different")
            {
                REQUIRE(fileName1 != fileName2);
            }

        }
    }
}

SCENARIO("UserScriptTests")
{
    GIVEN("A UserScript instance")
    {
        UserScript userScript;
        QDir dir(FileHelper::userScriptsDirectory());
        dir.removeRecursively();
        REQUIRE(!dir.exists());

        WHEN("importing a file that does not exists")
        {
            bool retVal = userScript.import("/an/invalid/path");
            THEN("import return value is false")
            {
                REQUIRE(!retVal);
            }
        }

        WHEN("importing a file that exists")
        {
            QByteArray fileContent("alert('custom user script')");
            QString sourceFilePath = "file://" + FileHelper::appDataDirectory() + "fakeUserScript.js";
            QFile file(FileHelper::appDataDirectory() + "fakeUserScript.js");
            file.open(QFile::WriteOnly);
            file.write(fileContent);
            file.close();

            bool retVal = userScript.import(sourceFilePath);

            THEN("import return value is true")
            {
                REQUIRE(retVal);

                AND_THEN("the file exists")
                {
                    REQUIRE(QFile::exists(userScript.path()));
                }

                AND_THEN("the file content is loaded and available via the code property")
                {
                    REQUIRE(userScript.code().toStdString() == fileContent.toStdString());
                }
            }
        }
    }
}
