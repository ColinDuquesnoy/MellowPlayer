#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>
#include <QObject>
#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilters.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilterFactory.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("PlatformFiltersTests")
{
    GIVEN("a PlatformFilters instance") {
        PlatformFilters filters;

        WHEN("filter is 'All'") {
            QString filter = "All";

            THEN("match always returns true") {
                REQUIRE(filters.match(filter));
            }
        }

#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    WHEN("filter is 'Linux'") {
            QString filter = "Linux";

            AND_WHEN("not in an AppImage") {
                qputenv("APPIMAGE", "");

                THEN("match returns true") {
                    REQUIRE(filters.match(filter));
                }
            }

            AND_WHEN("in an AppImage") {
                qputenv("APPIMAGE", "/path/to/appimage");

                THEN("match returns false") {
                    REQUIRE(!filters.match(filter));
                }

                qputenv("APPIMAGE", "");
            }
        }

        WHEN("filter is 'AppImage'") {
            QString filter = "AppImage";

            AND_WHEN("not in an AppImage") {
                qputenv("APPIMAGE", "");

                THEN("match returns false") {
                    REQUIRE(!filters.match(filter));
                }
            }

            AND_WHEN("in an AppImage") {
                qputenv("APPIMAGE", "/path/to/appimage");

                THEN("match returns true") {
                    REQUIRE(filters.match(filter));
                }

                qputenv("APPIMAGE", "");
            }
        }

        WHEN("filter is 'Linux-AppImage'") {
            QString filter = "Linux-AppImage";

            AND_WHEN("not in an AppImage") {
                qputenv("APPIMAGE", "");

                THEN("match returns true") {
                    REQUIRE(filters.match(filter));
                }
            }

            AND_WHEN("in an AppImage") {
                qputenv("APPIMAGE", "/path/to/appimage");

                THEN("match returns true") {
                    REQUIRE(filters.match(filter));
                }

                qputenv("APPIMAGE", "");
            }
        }

        WHEN("filter is 'Windows'") {
            QString filter = "Windows";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-Windows'") {
            QString filter = "Linux-Windows";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'OSX'") {
            QString filter = "OSX";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX'") {
            QString filter = "Linux-,OSX";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX-Windows'") {
            QString filter = "Linux-OSX-Windows";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }
#endif

#ifdef Q_OS_WIN
        WHEN("filter is 'Windows'") {
            QString filter = "Windows";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux'") {
            QString filter = "Linux";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'AppImage'") {
            QString filter = "AppImage";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'OSX'") {
            QString filter = "OSX";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }


        WHEN("filter is 'Linux-Windows'") {
            QString filter = "Linux-Windows";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX'") {
            QString filter = "Linux-OSX";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX-Windows'") {
            QString filter = "Linux-OSX-Windows";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }
#endif

#ifdef Q_OS_OSX
        WHEN("filter is 'OSX'") {
            QString filter = "OSX";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Windows'") {
            QString filter = "Windows";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux'") {
            QString filter = "Linux";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'AppImage'") {
            QString filter = "AppImage";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }


        WHEN("filter is 'Linux-Windows'") {
            QString filter = "Linux-Windows";

            THEN("match returns false") {
                REQUIRE(!filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX'") {
            QString filter = "Linux-OSX";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }

        WHEN("filter is 'Linux-OSX-Windows'") {
            QString filter = "Linux-OSX-Windows";

            THEN("match returns true") {
                REQUIRE(filters.match(filter));
            }
        }
#endif
    }
}
