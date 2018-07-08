#pragma once

#include <catch/catch.hpp>
#include <fakeit/fakeit.hpp>

#define Check(statement) \
    try { \
        statement; \
        REQUIRE(true); \
    }\
    catch(const FakeitException& e) {\
        INTERNAL_CATCH_MSG( Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::Normal, "FAIL", e.what() ); \
    }


//namespace MellowPlayer::Infrastructure::Tests
//{
//    class IFile;
//
//    auto blankDeleter = [](IFile*){};
//}

