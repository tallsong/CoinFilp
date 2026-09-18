#pragma once
// Workaround for Qt <= 6.10.x with Xcode 26+/27 clang on Apple Silicon:
// QtCore's qyieldcpu.h calls __yield(), which the newer compiler only
// declares once <arm_acle.h> has been included. This header is force-included
// via QMAKE_CXXFLAGS in CoinFilp.pro so the intrinsic is declared first.
#if defined(__aarch64__) || defined(__arm64__)
#include <arm_acle.h>
#endif
