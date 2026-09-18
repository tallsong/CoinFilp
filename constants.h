// Shared constants for the CoinFilp scenes.
#ifndef COINFILP_CONSTANTS_H_
#define COINFILP_CONSTANTS_H_

namespace coinfilp {

// Every scene window uses the same fixed size.
inline constexpr int kSceneWidth = 320;
inline constexpr int kSceneHeight = 588;

// Delay between pressing a navigation button and switching scenes, so the
// button's press animation and sound can finish first.
inline constexpr int kSceneSwitchDelayMs = 500;

// Resources shared by more than one scene.
inline constexpr char kWindowIcon[] = ":/img/Coin0001.png";
inline constexpr char kTitleImage[] = ":/img/Title.png";
inline constexpr char kBackButtonImage[] = ":/img/BackButton.png";
inline constexpr char kBackButtonPressedImage[] =
    ":/img/BackButtonSelected.png";
inline constexpr char kBackButtonSound[] = "qrc:/img/BackButtonSound.wav";

}  // namespace coinfilp

#endif  // COINFILP_CONSTANTS_H_
