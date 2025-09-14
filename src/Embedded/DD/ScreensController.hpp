#ifndef ScreenCONTROLLER_HPP
#define ScreenCONTROLLER_HPP

#include "ScreenInfo.hpp"
#include "ScreenLapTime.hpp"
#include "ScreenMessage.hpp"
#include "ScreenNumber.hpp"
#include "ScreenStartupAnim.hpp"

class ScreensController {
 public:
  ScreensController(ILI9341_t3n &left, ILI9341_t3n &right);

  /** Destructor */
  ~ScreensController();

  /** Copy constructor disabled */
  ScreensController(const ScreensController &) = delete;
  /** Assignment operator disabled */
  void operator=(const ScreensController &) = delete;

  /// the different states that the screens can be in. Please note that states
  /// should include transitionary states, such as ScreenBegin before Screen or
  /// whatever
  enum ScreenStates { /*StartupLeft, StartupRight,*/ speedInfo,
                      InfoScreen1,
                      InfoScreen2,
                      InfoScreen3,
                      Notification,
                      LapTime,
                      Titan };

  /**
   * Gets the current state of the screen
   * @returns the screen state
   */
  int GetState() { return state_; }

  void Update(unsigned long &elapsed);
  void Initialize();
  void OnButtonPressUp(); // page up
  void OnButtonPressDown(); // page down
  void OnMessage(String message);
  void OnNewLap();

  /**
   *  Returns true if the a notification/message state is active
   */
  bool IsNotificationActive() const {
    return state_ == Notification || state_ == LapTime;
  }

 private:
  ILI9341_t3n &display_left_;
  ILI9341_t3n &display_right_;

  void SetState(ScreenStates state);

  ScreenStates state_;                  ///< screen states
  ScreenStates state_prev_ = InfoScreen1;  ///< Used to return to previous screen
                                        ///< states after temporary states
  unsigned long state_start_time_ =
      0;  ///< The time in milliseconds that the current state started

  unsigned long msg_display_duration_ =
      5000;  ///< The time in milliseconds to display a message when recieved
  unsigned long lap_time_display_duration_ =
      5000;  ///< The time in milliseconds to display a laptime when triggered

  unsigned long obd_display_duration_ = 2000;

  /* Screen definitions */
  ScreenStartupAnim *startup_screen_left_ = nullptr;
  ScreenStartupAnim *startup_screen_right_ = nullptr;

  ScreenInfo *info_screen_1_left_ = nullptr;
  ScreenInfo *info_screen_1_right_ = nullptr;

  ScreenInfo *info_screen_2_left_ = nullptr;
  ScreenInfo *info_screen_2_right_ = nullptr;

  ScreenInfo *info_screen_3_left_ = nullptr;
  ScreenInfo *info_screen_3_right_ = nullptr;

  ScreenMessage *message_screen_ = nullptr;

  ScreenNumber *speed_screen_ = nullptr;

  ScreenLapTime *lap_time_screen_ = nullptr;
};

/**
 * Constructor
 *
 * Constructs screens for all of the states and then sets the initial state
 */
ScreensController::ScreensController(ILI9341_t3n &left, ILI9341_t3n &right)
    : display_left_(left), display_right_(right) {
  /* speed screen */
  speed_screen_ = new ScreenNumber(display_left_, VCU_driveSpeed, "SPD:");

  /* Info screen 1 */
  info_screen_1_left_ = new ScreenInfo(display_left_);
  /*
  info_screen_1_left_->SetSignal(1, &C50_gpsSpeed, "SPD:", "%3.1f");
  info_screen_1_left_->SetSignal(2, &VCU_brakeBias, "BIAS:", "%3.0f%");
  info_screen_1_left_->SetSignal(3, &BMS_highestTemp, "BMST:", "%3.0f");
  info_screen_1_left_->SetSignal(4, &PM_commandedTorque, "CMDT:", "%3.0f");
  */
  /* Info screen 3 */
  info_screen_1_left_ = new ScreenInfo(display_left_);
  info_screen_1_left_->SetSignal(1, &VCU_driveSpeed, "MPH:", "%4.1f");
  info_screen_1_left_->SetSignal(2, &PM_motorTemp, "MT:", "%4.1f");
  info_screen_1_left_->SetSignal(3, &STMM_seg3ThermValAvg, "SEGT:", "%4.1f");
  info_screen_1_left_->SetSignal(4, &PM_moduleBTemp, "INVT:", "%4.1f");

  info_screen_1_right_ = new ScreenInfo(display_right_);
  info_screen_1_right_->SetSignal(1, &PM_dcBusVolt, "HV:", "%4.1f");
  info_screen_1_right_->SetSignal(2, &PDM_pdmVoltAvg, "LV:", "%3.1f");
  info_screen_1_right_->SetSignal(3, &VCU_radFanLDuty, "FAN:", "%3.0f%");
  info_screen_1_right_->SetSignal(4, &PM_commandedTorque, "CMDT:", "%3.0f%");

  /* Info screen 2 */
  info_screen_2_left_ = new ScreenInfo(display_left_);
  info_screen_2_left_->SetSignal(1, &VCU_brakePressureF, "BPF:", "%4.1f");
  info_screen_2_left_->SetSignal(2, &VCU_brakePressureR, "BPR:", "%4.1f");
  info_screen_2_left_->SetSignal(3, &VCU_throttlePosition, "TPS:", "%3.1f%");
  info_screen_2_left_->SetSignal(4, &PM_motorSpeed, "RPM:", "%4.0f");
  // info_screen_2_left_->SetSignal(4, &ATCCR_shiftingPressure, "SFT:", "%3.1f");

  /* Info screen 3 */
  info_screen_3_left_ = new ScreenInfo(display_left_);
  info_screen_3_left_->SetSignal(1, &PM_motorSpeed, "RPM:", "%4.0f");
  info_screen_3_left_->SetSignal(2, &PM_motorTemp, "MT:", "%4.1f");
  info_screen_3_left_->SetSignal(3, &PM_outputVolt, "OUTV:", "%4.1f");
  info_screen_3_left_->SetSignal(4, &PM_commandedTorque, "CMDT:", "%3.0f");
  
  // keep the same screen on the right side
  info_screen_2_right_ = info_screen_1_right_;
  info_screen_3_right_ = info_screen_1_right_;

  /* message screen */
  message_screen_ = new ScreenMessage(display_left_);

  /* laptime */
  lap_time_screen_ = new ScreenLapTime(display_left_);
}

/**
 * Destructor
 *
 * Destructs all dynamically allocated things
 */
ScreensController::~ScreensController() {
  /* speed */
  delete speed_screen_;

  /* Screen 1 */
  delete info_screen_1_left_;
  delete info_screen_1_right_;

  /* Screen 2 */
  delete info_screen_2_left_;

  /* Screen 3 */
  delete info_screen_3_left_;

  /* message display */
  delete message_screen_;

  /* laptime */
  delete lap_time_screen_;
}

/**
 * Initialize
 *
 * Sets the first state for the controller
 */
void ScreensController::Initialize() { SetState(InfoScreen1); }

/**
 * Update
 *
 * This is called as frequently as possible. If the time is allowable for an
 * update the updates are processed and the screens are written. \param elapsed
 * The time in milliseconds since the update method was last called
 */
void ScreensController::Update(unsigned long &elapsed) {
  switch (state_) {
    // case StartupLeft:
    //     startup_screen_left_->Update(elapsed);
    //     if (startup_screen_left_->IsCompleted()){
    //         SetState(StartupRight);
    //     }
    //     break;

    // case StartupRight:
    //     startup_screen_right_->Update(elapsed);
    //     if (startup_screen_right_->IsCompleted()){
    //         SetState(InfoScreen1);
    //     }
    //     break;
    case speedInfo:
      speed_screen_->Update(elapsed);
      info_screen_1_right_->Update(elapsed);
      break;

    case InfoScreen1:
      info_screen_1_left_->Update(elapsed);
      info_screen_1_right_->Update(elapsed);
      break;

    case InfoScreen2:
      info_screen_2_left_->Update(elapsed);
      info_screen_2_right_->Update(elapsed);
      break;

    case InfoScreen3:
      info_screen_3_left_->Update(elapsed);
      info_screen_3_right_->Update(elapsed);
      break;

    case Notification:
      message_screen_->Update(elapsed);

      // update the last state's right screen, too!
      switch (state_prev_) {
        case InfoScreen1:  // fall through
        case speedInfo:
          info_screen_1_right_->Update(elapsed);
          break;
        case InfoScreen2:
          info_screen_2_right_->Update(elapsed);
          break;
        case InfoScreen3:
          info_screen_3_right_->Update(elapsed);
          break;
        case Notification:
          break;
        case LapTime:
          break;
        case Titan:
          break;
      }

      // if the state is complete, set a new state
      /*
      if(M400_groundSpeedLeft.value() > 2 && millis() - state_start_time_ > obd_display_duration_) {
        SetState(state_prev_);
      } else if(millis() - state_start_time_ > msg_display_duration_) {
        SetState(state_prev_);
      }
      */
  
      break;

    case LapTime:
      lap_time_screen_->Update(elapsed);
      // update the last state's right screen, too!
      switch (state_prev_) {
        case InfoScreen1:  // fall through
        case speedInfo:
          info_screen_1_right_->Update(elapsed);
          break;
        case InfoScreen2:
          info_screen_2_right_->Update(elapsed);
          break;
        case InfoScreen3:
          info_screen_3_right_->Update(elapsed);
          break;
        case Notification:
          break;
        case LapTime:
          break;
        case Titan:
          break;
      }

      // if the state is complete, set a new state
      if (millis() - state_start_time_ > lap_time_display_duration_) {
        SetState(state_prev_);
      }
      break;

    case Titan:
      break;
  }
}

/**
 * Used internally to set the state of the screens. Handles exit and enter
 * funcitonality for the screens.
 *
 * \param state The state to set
 */
void ScreensController::SetState(ScreenStates state) {
  /*
   * State exiting actions
   */
  switch (state_) {
    // case StartupLeft:
    //     break;
    // case StartupRight:
    //     break;
    case speedInfo:
      break;
    case InfoScreen1:
      break;
    case InfoScreen2:
      break;
    case InfoScreen3:
      break;
    case LapTime:  // fall through
    case Notification:
      // in order to prevent getting stuck in the Notification state,
      // set the state to the previous state. That way, it's like
      // the notificaion state never existed, since after the next 10ish lines
      // of code, the previous state will be two states ago, and the current
      // state will be the last previous state... confusing but yeah
      state_ = state_prev_;
      break;
    case Titan:
      break;
  }

  /*
   * Set the state
   */
  state_prev_ = state_;          // move current to previous state
  state_ = state;                // move new input state to current state
  state_start_time_ = millis();  // update state start time

  /*
   * State entering actions
   */
  switch (state_) {
    // case StartupLeft:
    //     startup_screen_left_->Initialize();
    //     break;
    // case StartupRight:
    //     startup_screen_right_->Initialize();
    //     break;
    case speedInfo:
      speed_screen_->Initialize();
      info_screen_1_right_->Initialize();
      break;
    case InfoScreen1:
      info_screen_1_left_->Initialize();
      info_screen_1_right_->Initialize();
      break;
    case InfoScreen2:
      info_screen_2_left_->Initialize();
      info_screen_2_right_->Initialize();
      break;
    case InfoScreen3:
      info_screen_3_left_->Initialize();
      info_screen_3_right_->Initialize();
      break;
    case Notification:
      message_screen_->Initialize();
      break;
    case LapTime:
      lap_time_screen_->Initialize();
      break;
    case Titan:
      break;
  }
}

/**
 * Called when the control button is pressed. This can either change the screen
 * state or disable the current notification screen.
 */

void ScreensController::OnButtonPressUp() {
  switch (state_) {
    // case StartupLeft:
    //     SetState(InfoScreen1);
    //     break;
    // case StartupRight:
    //     SetState(InfoScreen1);
    //     break;
    case speedInfo:
      SetState(InfoScreen1);
      break;
    case InfoScreen1:
      SetState(InfoScreen2);
      break;
    case InfoScreen2:
      SetState(InfoScreen3);
      break;
    case InfoScreen3:
      SetState(speedInfo);
      break;
    case Notification:  // fal through
    case LapTime:
      SetState(state_prev_);
      break;
    case Titan:
      break;
  }
}

void ScreensController::OnButtonPressDown() {
  switch (state_) {
    // case StartupLeft:
    //     SetState(InfoScreen1);
    //     break;
    // case StartupRight:
    //     SetState(InfoScreen1);
    //     break;
    case speedInfo:
      SetState(InfoScreen3);
      break;
    case InfoScreen1:
      SetState(speedInfo);
      break;
    case InfoScreen2:
      SetState(InfoScreen1);
      break;
    case InfoScreen3:
      SetState(InfoScreen2);
      break;
    case Notification:  // fal through
    case LapTime:
      SetState(state_prev_);
      break;
    case Titan:
      break;
  }
}


/**
 * What to do when a message is recieved
 * \param msg The message to display
 */
void ScreensController::OnMessage(String msg) {
  if (message_screen_) {
    message_screen_->SetMessage(msg);
  }
  SetState(Notification);
}

/**
 * Called when a new lap is triggered
 */
void ScreensController::OnNewLap() {
  if (lap_time_screen_) {
    SetState(LapTime);
  }
}

#endif
