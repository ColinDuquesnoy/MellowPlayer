import qbs
import CatchTest

CatchTest {
    layer: "Mpris"
    kind: "IntegrationTests"
    condition: platform.unix

    Depends { name: "platform" }
}
