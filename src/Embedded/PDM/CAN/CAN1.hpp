/******************************************************************************
    
    This file was generated automatically from a DBC file by the dbctocpp 
    utility, which is part of the StateCAN library, 
    a component of SR-Libraries.

    https://github.com/msfrt/SR-Libraries
    
******************************************************************************/

#ifndef CAN1_HPP
#define CAN1_HPP

#include <FlexCAN_T4.h>
#include <StateCAN.h>

// Message: VCU_201 [0xc9]
StateSignal VCU_counterMsg201(4, false, 1, 0.0, 0, 15, 0.0, -1, 201);
StateSignal VCU_radFanLDuty(16, true, 10, 0.0, 0, 100, 0.0, -1, 201);
StateSignal VCU_radFanRDuty(16, true, 10, 0.0, 0, 100, 0.0, -1, 201);
StateSignal VCU_waterPumpDuty(16, true, 10, 0.0, 0, 100, 0.0, -1, 201);

// Message: DCDC_1801D08F [0x1801d08f]
StateSignal DCDC_voltageOutput(16, false, 10, 0.0, 0, 6553, 0.0, -1, 402772111);
StateSignal DCDC_currentOutput(16, false, 10, 0.0, 0, 6553, 0.0, -1, 402772111);
StateSignal DCDC_ready(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_status(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_hardwareFault(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_canError(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_fanControl1(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_shutOffError(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_fanControl2(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_hvilError(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_tempWarning(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_overTempError(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_inputOverVoltage(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_inputUnderVoltage(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_outputOverVoltage(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_outputUnderVoltage(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_outputOverCurrent(1, false, 1, 0.0, 0, 1, 0.0, -1, 402772111);
StateSignal DCDC_temperature(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 402772111);

// Message: PM_194 [0xc2]
StateSignal PM_parameterAddressResponse(16, false, 1, 0.0, 0, 65535, 0.0, -1, 194);
StateSignal PM_writeSuccess(1, false, 1, 0.0, 0, 1, 0.0, -1, 194);
StateSignal PM_dataResponse(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 194);

// Message: PM_176 [0xb0]
StateSignal PM_fastTorqueCommand(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 176);
StateSignal PM_fastTorqueFeedback(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 176);
StateSignal PM_fastMotorSpeed(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 176);
StateSignal PM_fastDCBusVolt(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 176);

// Message: PM_175 [0xaf]
StateSignal PM_bufferRecord(8, false, 1, 0.0, 0, 255, 0.0, -1, 175);
StateSignal PM_bufferSegment(8, false, 1, 0.0, 0, 255, 0.0, -1, 175);
StateSignal PM_diagData1(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 175);
StateSignal PM_diagData2(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 175);
StateSignal PM_diagData3(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 175);

// Message: PM_174 [0xae]
StateSignal PM_projectCodeEEPVer(16, false, 1, 0.0, 0, 65535, 0.0, -1, 174);
StateSignal PM_swVersion(16, false, 1, 0.0, 0, 65535, 0.0, -1, 174);
StateSignal PM_datecodeMMDD(16, false, 1, 0.0, 0, 65535, 0.0, -1, 174);
StateSignal PM_datecodeYYYY(16, false, 1, 0.0, 0, 65535, 0.0, -1, 174);

// Message: PM_173 [0xad]
StateSignal PM_modulationIndex(16, true, 10000, 0.0, -3, 3, 0.0, -1, 173);
StateSignal PM_fluxWeakeningOutput(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 173);
StateSignal PM_idCommand(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 173);
StateSignal PM_iqCommand(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 173);

// Message: PM_172 [0xac]
StateSignal PM_commandedTorque(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 172);
StateSignal PM_torqueFeedback(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 172);
StateSignal PM_powerOnTimer(32, false, 333, 0.0, 0, 12884901, 0.0, -1, 172);

// Message: PM_171 [0xab]
StateSignal PM_postFaultLo(16, false, 1, 0.0, 0, 65535, 0.0, -1, 171);
StateSignal PM_postFaultHi(16, false, 1, 0.0, 0, 65535, 0.0, -1, 171);
StateSignal PM_runFaultLo(16, false, 1, 0.0, 0, 65535, 0.0, -1, 171);
StateSignal PM_runFaultHi(16, false, 1, 0.0, 0, 65535, 0.0, -1, 171);

// Message: PM_169 [0xa9]
StateSignal PM_refVolt15(16, true, 100, 0.0, -327, 327, 0.0, -1, 169);
StateSignal PM_refVolt25(16, true, 100, 0.0, -327, 327, 0.0, -1, 169);
StateSignal PM_refVolt50(16, true, 100, 0.0, -327, 327, 0.0, -1, 169);
StateSignal PM_refVolt120(16, true, 100, 0.0, -327, 327, 0.0, -1, 169);

// Message: PM_168 [0xa8]
StateSignal PM_fluxCommand(16, true, 1000, 0.0, -32, 32, 0.0, -1, 168);
StateSignal PM_fluxFeedback(16, true, 1000, 0.0, -32, 32, 0.0, -1, 168);
StateSignal PM_id(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 168);
StateSignal PM_iq(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 168);

// Message: PM_167 [0xa7]
StateSignal PM_dcBusVolt(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 167);
StateSignal PM_outputVolt(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 167);
StateSignal PM_vabVdVolt(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 167);
StateSignal PM_vbcVqVolt(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 167);

// Message: PM_166 [0xa6]
StateSignal PM_phaseACurrent(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 166);
StateSignal PM_phaseBCurrent(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 166);
StateSignal PM_phaseCCurrent(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 166);
StateSignal PM_dcBusCurrent(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 166);

// Message: PM_165 [0xa5]
StateSignal PM_electricalMotorAngle(16, false, 10, 0.0, 0, 6553, 0.0, -1, 165);
StateSignal PM_motorSpeed(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 165);
StateSignal PM_electricalOutputFrequency(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 165);
StateSignal PM_deltaResolverFiltered(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 165);

// Message: PM_164 [0xa4]
StateSignal PM_digitalInputStatus1(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);
StateSignal PM_digitalInputStatus2(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);
StateSignal PM_digitalInputStatus3(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);
StateSignal PM_digitalInputStatus4(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);
StateSignal PM_digitalInputStatus5(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);
StateSignal PM_digitalInputStatus6(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);
StateSignal PM_digitalInputStatus7(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);
StateSignal PM_digitalInputStatus8(1, false, 1, 0.0, 0, 1, 0.0, -1, 164);

// Message: PM_163 [0xa3]
StateSignal PM_analogInputVolt1(10, false, 100, 0.0, 0, 10, 0.0, -1, 163);
StateSignal PM_analogInputVolt2(10, false, 100, 0.0, 0, 10, 0.0, -1, 163);
StateSignal PM_analogInputVolt3(10, false, 100, 0.0, 0, 10, 0.0, -1, 163);
StateSignal PM_analogInputVolt4(10, false, 100, 0.0, 0, 10, 0.0, -1, 163);
StateSignal PM_analogInputVolt5(10, false, 100, 0.0, 0, 10, 0.0, -1, 163);
StateSignal PM_analogInputVolt6(10, false, 100, 0.0, 0, 10, 0.0, -1, 163);

// Message: PM_162 [0xa2]
StateSignal PM_rtd4Temp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 162);
StateSignal PM_rtd5Temp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 162);
StateSignal PM_motorTemp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 162);
StateSignal PM_torqueShudder(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 162);

// Message: PM_161 [0xa1]
StateSignal PM_controlBoardTemp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 161);
StateSignal PM_rtd1Temp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 161);
StateSignal PM_rtd2Temp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 161);
StateSignal PM_rtd3Temp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 161);

// Message: PM_160 [0xa0]
StateSignal PM_moduleATemp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 160);
StateSignal PM_moduleBTemp(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 160);
StateSignal PM_moduleCTemp(16, true, 10, 0.0, 0, 0, 0.0, -1, 160);
StateSignal PM_gateDriverBoardTemp(16, true, 10, 0.0, 0, 0, 0.0, -1, 160);

// Message: VCU_193 [0xc1]
StateSignal VCU_pmParameterAddressCommand(16, false, 1, 0.0, 0, 65535, 0.0, -1, 193);
StateSignal VCU_pmReadWriteCommand(1, false, 1, 0.0, 0, 1, 0.0, -1, 193);
StateSignal VCU_pmDataCommand(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 193);

// Message: VCU_18008FD0 [0x18008fd0]
StateSignal VCU_dcdcProtect(2, false, 1, 0.0, 0, 0, 0.0, -1, 402690000);
StateSignal VCU_dcdcEnable(2, false, 1, 0.0, 0, 0, 0.0, -1, 402690000);

// Message: C50_454 [0x1c6]
StateSignal C50_gpsSigIndicator(32, false, 1, 0.0, 0, 3, 0.0, -1, 454);

// Message: C50_453 [0x1c5]
StateSignal C50_gpsHsec(32, false, 1, 0.0, 0, 99, 0.0, -1, 453);
StateSignal C50_gpsSec(32, false, 1, 0.0, 0, 59, 0.0, -1, 453);

// Message: C50_452 [0x1c4]
StateSignal C50_gpsElevation(32, true, 1, 0.0, -5000, 5000, 0.0, -1, 452);
StateSignal C50_gpsFix(32, false, 1, 0.0, 0, 3, 0.0, -1, 452);

// Message: C50_451 [0x1c3]
StateSignal C50_gpsSpeed(32, true, 1, 0.0, 0, 0, 0.0, -1, 451);
StateSignal C50_gpsDirection(32, true, 1, 0.0, -360, 360, 0.0, -1, 451);

// Message: C50_450 [0x1c2]
StateSignal C50_gpsLat(32, true, 1, 0.0, -90, 90, 0.0, -1, 450);
StateSignal C50_gpsLong(32, true, 1, 0.0, -180, 180, 0.0, -1, 450);

// Message: ATCC_303 [0x12f]
StateSignal ATCC_counterMsg303(4, false, 1, 0.0, 0, 15, 0.0, -1, 303);
StateSignal ATCC_coolantTempMotorIn(16, true, 10, 0.0, 0, 120, 0.0, -1, 303);
StateSignal ATCC_coolantTempInverterIn(16, true, 10, 0.0, 0, 120, 0.0, -1, 303);
StateSignal ATCC_coolantTempInverterOut(16, true, 10, 0.0, 0, 120, 0.0, -1, 303);

// Message: ATCC_302 [0x12e]
StateSignal ATCC_counterMsg302(4, false, 1, 0.0, 0, 15, 0.0, -1, 302);
StateSignal ATCC_angularWheelFreqRL(16, false, 1, 0.0, 0, 2000, 0.0, -1, 302);
StateSignal ATCC_angularWheelFreqRR(16, false, 1, 0.0, 0, 2000, 0.0, -1, 302);

// Message: ATCC_301 [0x12d]
StateSignal ATCC_counterMsg301(4, false, 1, 0.0, 0, 15, 0.0, -1, 301);
StateSignal ATCC_angularWheelFreqFL(16, false, 1, 0.0, 0, 2000, 0.0, -1, 301);
StateSignal ATCC_angularWheelFreqFR(16, false, 1, 0.0, 0, 2000, 0.0, -1, 301);

// Message: ATCC_300 [0x12c]
StateSignal ATCC_counterMsg300(4, false, 1, 0.0, 0, 15, 0.0, -1, 300);
StateSignal ATCC_boardTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 300);
StateSignal ATCC_teensyTemp(16, true, 10, 0.0, 0, 150, 0.0, -1, 300);

// Message: LWS_1984 [0x7c0]
StateSignal LWS_ccw(1, false, 1, 0.0, 0, 1, 0.0, -1, 1984);

// Message: LWS_688 [0x2b0]
StateSignal LWS_angle(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 688);
StateSignal LWS_speed(8, false, 0, 0.0, 0, 1020, 0.0, -1, 688);
StateSignal LWS_ok(1, false, 1, 0.0, 0, 1, 0.0, -1, 688);
StateSignal LWS_cal(1, false, 1, 0.0, 0, 1, 0.0, -1, 688);
StateSignal LWS_trim(1, false, 1, 0.0, 0, 1, 0.0, -1, 688);

// Message: VCU_200 [0xc8]
StateSignal VCU_counterMsg200(4, false, 1, 0.0, 0, 15, 0.0, -1, 200);
StateSignal VCU_brakeLightCmd(1, false, 1, 0.0, 0, 1, 0.0, -1, 200);
StateSignal VCU_segmentHalf1Duty(16, true, 10, 0.0, 0, 100, 0.0, -1, 200);
StateSignal VCU_segmentHalf2Duty(16, true, 10, 0.0, 0, 100, 0.0, -1, 200);

// Message: VCU_192 [0xc0]
StateSignal VCU_torqueCommand(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 192);
StateSignal VCU_speedCommand(16, true, 1, 0.0, -32768, 32767, 0.0, -1, 192);
StateSignal VCU_directionCommand(1, false, 1, 0.0, 0, 1, 0.0, -1, 192);
StateSignal VCU_inverterEnable(1, false, 1, 0.0, 0, 1, 0.0, -1, 192);
StateSignal VCU_inverterDischarge(1, false, 1, 0.0, 0, 1, 0.0, -1, 192);
StateSignal VCU_speedModeEnable(1, false, 1, 0.0, 0, 1, 0.0, -1, 192);
StateSignal VCU_counterMsg192(4, false, 1, 0.0, 0, 15, 0.0, -1, 192);
StateSignal VCU_torqueLimitCommand(16, true, 10, 0.0, -3276, 3276, 0.0, -1, 192);

// Message: PM_170 [0xaa]
StateSignal PM_vsmState(8, false, 1, 0.0, 0, 15, 0.0, -1, 170);
StateSignal PM_pwmFrequency(8, false, 1, 0.0, 0, 255, 0.0, -1, 170);
StateSignal PM_inverterState(8, false, 1, 0.0, 0, 255, 0.0, -1, 170);
StateSignal PM_relayStatus1(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_relayStatus2(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_relayStatus3(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_relayStatus4(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_relayStatus5(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_relayStatus6(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_inverterRunMode(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_inverterDischargeMode(3, false, 1, 0.0, 0, 7, 0.0, -1, 170);
StateSignal PM_inverterCommandMode(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_counterMsg170(4, false, 1, 0.0, 0, 15, 0.0, -1, 170);
StateSignal PM_inverterEnableState(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_startModeActive(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_inverterEnableLockout(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_directionCommand(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_bmsActive(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_bmsTorqueLimiting(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_maxSpeedLimiting(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);
StateSignal PM_lowSpeedLimiting(1, false, 1, 0.0, 0, 1, 0.0, -1, 170);




/************************************************************************************
    
    Incoming CAN frame decoding functions

************************************************************************************/


/*
 * Decode a CAN frame for the message VCU_201
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_201(const CAN_message_t &imsg) {

	VCU_counterMsg201.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_radFanLDuty.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	VCU_radFanRDuty.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	VCU_waterPumpDuty.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message DCDC_1801D08F
 * \param imsg A reference to the incoming CAN message frame
 */
void read_DCDC_1801D08F(const CAN_message_t &imsg) {

	DCDC_voltageOutput.set_can_value((imsg.buf[1]) | (imsg.buf[0] << 8));
	DCDC_currentOutput.set_can_value((imsg.buf[3]) | (imsg.buf[2] << 8));
	DCDC_ready.set_can_value(((imsg.buf[4] & 0b00000001)));
	DCDC_status.set_can_value((((imsg.buf[4] & 0b00000010)) >> 1));
	DCDC_hardwareFault.set_can_value((((imsg.buf[4] & 0b00000100)) >> 2));
	DCDC_canError.set_can_value((((imsg.buf[4] & 0b00001000)) >> 3));
	DCDC_fanControl1.set_can_value((((imsg.buf[4] & 0b00010000)) >> 4));
	DCDC_shutOffError.set_can_value((((imsg.buf[4] & 0b00100000)) >> 5));
	DCDC_fanControl2.set_can_value((((imsg.buf[4] & 0b01000000)) >> 6));
	DCDC_hvilError.set_can_value((((imsg.buf[4] & 0b10000000)) >> 7));
	DCDC_tempWarning.set_can_value(((imsg.buf[5] & 0b00000001)));
	DCDC_overTempError.set_can_value((((imsg.buf[5] & 0b00000010)) >> 1));
	DCDC_inputOverVoltage.set_can_value((((imsg.buf[5] & 0b00000100)) >> 2));
	DCDC_inputUnderVoltage.set_can_value((((imsg.buf[5] & 0b00001000)) >> 3));
	DCDC_outputOverVoltage.set_can_value((((imsg.buf[5] & 0b00010000)) >> 4));
	DCDC_outputUnderVoltage.set_can_value((((imsg.buf[5] & 0b00100000)) >> 5));
	DCDC_outputOverCurrent.set_can_value((((imsg.buf[5] & 0b01000000)) >> 6));
	DCDC_temperature.set_can_value((imsg.buf[7]) | (imsg.buf[6] << 8));

}

/*
 * Decode a CAN frame for the message PM_194
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_194(const CAN_message_t &imsg) {

	PM_parameterAddressResponse.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_writeSuccess.set_can_value(((imsg.buf[2] & 0b00000001)));
	PM_dataResponse.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message PM_176
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_176(const CAN_message_t &imsg) {

	PM_fastTorqueCommand.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_fastTorqueFeedback.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_fastMotorSpeed.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_fastDCBusVolt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_175
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_175(const CAN_message_t &imsg) {

	PM_bufferRecord.set_can_value((imsg.buf[0]));
	PM_bufferSegment.set_can_value((imsg.buf[1]));
	PM_diagData1.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_diagData2.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_diagData3.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_174
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_174(const CAN_message_t &imsg) {

	PM_projectCodeEEPVer.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_swVersion.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_datecodeMMDD.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_datecodeYYYY.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_173
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_173(const CAN_message_t &imsg) {

	PM_modulationIndex.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_fluxWeakeningOutput.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_idCommand.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_iqCommand.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_172
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_172(const CAN_message_t &imsg) {

	PM_commandedTorque.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_torqueFeedback.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_powerOnTimer.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8) | (imsg.buf[6] << 16) | (imsg.buf[7] << 24));

}

/*
 * Decode a CAN frame for the message PM_171
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_171(const CAN_message_t &imsg) {

	PM_postFaultLo.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_postFaultHi.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_runFaultLo.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_runFaultHi.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_169
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_169(const CAN_message_t &imsg) {

	PM_refVolt15.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_refVolt25.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_refVolt50.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_refVolt120.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_168
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_168(const CAN_message_t &imsg) {

	PM_fluxCommand.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_fluxFeedback.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_id.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_iq.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_167
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_167(const CAN_message_t &imsg) {

	PM_dcBusVolt.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_outputVolt.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_vabVdVolt.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_vbcVqVolt.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_166
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_166(const CAN_message_t &imsg) {

	PM_phaseACurrent.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_phaseBCurrent.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_phaseCCurrent.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_dcBusCurrent.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_165
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_165(const CAN_message_t &imsg) {

	PM_electricalMotorAngle.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_motorSpeed.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_electricalOutputFrequency.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_deltaResolverFiltered.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_164
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_164(const CAN_message_t &imsg) {

	PM_digitalInputStatus1.set_can_value(((imsg.buf[0] & 0b00000001)));
	PM_digitalInputStatus2.set_can_value(((imsg.buf[1] & 0b00000001)));
	PM_digitalInputStatus3.set_can_value(((imsg.buf[2] & 0b00000001)));
	PM_digitalInputStatus4.set_can_value(((imsg.buf[3] & 0b00000001)));
	PM_digitalInputStatus5.set_can_value(((imsg.buf[4] & 0b00000001)));
	PM_digitalInputStatus6.set_can_value(((imsg.buf[5] & 0b00000001)));
	PM_digitalInputStatus7.set_can_value(((imsg.buf[6] & 0b00000001)));
	PM_digitalInputStatus8.set_can_value(((imsg.buf[7] & 0b00000001)));

}

/*
 * Decode a CAN frame for the message PM_163
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_163(const CAN_message_t &imsg) {

	PM_analogInputVolt1.set_can_value((imsg.buf[0]) | ((imsg.buf[1] & 0b00000011) << 8));
	PM_analogInputVolt2.set_can_value((((imsg.buf[1] & 0b11111100)) | ((imsg.buf[2] & 0b00001111) << 8) >> 2));
	PM_analogInputVolt3.set_can_value((((imsg.buf[2] & 0b11110000)) | ((imsg.buf[3] & 0b00111111) << 8) >> 4));
	PM_analogInputVolt4.set_can_value((imsg.buf[4]) | ((imsg.buf[5] & 0b00000011) << 8));
	PM_analogInputVolt5.set_can_value((((imsg.buf[5] & 0b11111100)) | ((imsg.buf[6] & 0b00001111) << 8) >> 2));
	PM_analogInputVolt6.set_can_value((((imsg.buf[6] & 0b11110000)) | ((imsg.buf[7] & 0b00111111) << 8) >> 4));

}

/*
 * Decode a CAN frame for the message PM_162
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_162(const CAN_message_t &imsg) {

	PM_rtd4Temp.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_rtd5Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_motorTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_torqueShudder.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_161
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_161(const CAN_message_t &imsg) {

	PM_controlBoardTemp.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_rtd1Temp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_rtd2Temp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_rtd3Temp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_160
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_160(const CAN_message_t &imsg) {

	PM_moduleATemp.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	PM_moduleBTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PM_moduleCTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PM_gateDriverBoardTemp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message VCU_193
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_193(const CAN_message_t &imsg) {

	VCU_pmParameterAddressCommand.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	VCU_pmReadWriteCommand.set_can_value(((imsg.buf[2] & 0b00000001)));
	VCU_pmDataCommand.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message VCU_18008FD0
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_18008FD0(const CAN_message_t &imsg) {

	VCU_dcdcProtect.set_can_value((((imsg.buf[0] & 0b00001100)) >> 2));
	VCU_dcdcEnable.set_can_value(((imsg.buf[0] & 0b00000011)));

}

/*
 * Decode a CAN frame for the message C50_454
 * \param imsg A reference to the incoming CAN message frame
 */
void read_C50_454(const CAN_message_t &imsg) {

	C50_gpsSigIndicator.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8) | (imsg.buf[2] << 16) | (imsg.buf[3] << 24));

}

/*
 * Decode a CAN frame for the message C50_453
 * \param imsg A reference to the incoming CAN message frame
 */
void read_C50_453(const CAN_message_t &imsg) {

	C50_gpsHsec.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8) | (imsg.buf[2] << 16) | (imsg.buf[3] << 24));
	C50_gpsSec.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8) | (imsg.buf[6] << 16) | (imsg.buf[7] << 24));

}

/*
 * Decode a CAN frame for the message C50_452
 * \param imsg A reference to the incoming CAN message frame
 */
void read_C50_452(const CAN_message_t &imsg) {

	C50_gpsElevation.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8) | (imsg.buf[2] << 16) | (imsg.buf[3] << 24));
	C50_gpsFix.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8) | (imsg.buf[6] << 16) | (imsg.buf[7] << 24));

}

/*
 * Decode a CAN frame for the message C50_451
 * \param imsg A reference to the incoming CAN message frame
 */
void read_C50_451(const CAN_message_t &imsg) {

	C50_gpsSpeed.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8) | (imsg.buf[2] << 16) | (imsg.buf[3] << 24));
	C50_gpsDirection.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8) | (imsg.buf[6] << 16) | (imsg.buf[7] << 24));

}

/*
 * Decode a CAN frame for the message C50_450
 * \param imsg A reference to the incoming CAN message frame
 */
void read_C50_450(const CAN_message_t &imsg) {

	C50_gpsLat.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8) | (imsg.buf[2] << 16) | (imsg.buf[3] << 24));
	C50_gpsLong.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8) | (imsg.buf[6] << 16) | (imsg.buf[7] << 24));

}

/*
 * Decode a CAN frame for the message ATCC_303
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCC_303(const CAN_message_t &imsg) {

	ATCC_counterMsg303.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCC_coolantTempMotorIn.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCC_coolantTempInverterIn.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCC_coolantTempInverterOut.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCC_302
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCC_302(const CAN_message_t &imsg) {

	ATCC_counterMsg302.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCC_angularWheelFreqRL.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCC_angularWheelFreqRR.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCC_301
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCC_301(const CAN_message_t &imsg) {

	ATCC_counterMsg301.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCC_angularWheelFreqFL.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCC_angularWheelFreqFR.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message ATCC_300
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCC_300(const CAN_message_t &imsg) {

	ATCC_counterMsg300.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCC_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCC_teensyTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message LWS_1984
 * \param imsg A reference to the incoming CAN message frame
 */
void read_LWS_1984(const CAN_message_t &imsg) {

	LWS_ccw.set_can_value((((imsg.buf[0] & 0b00000100)) >> 2));

}

/*
 * Decode a CAN frame for the message LWS_688
 * \param imsg A reference to the incoming CAN message frame
 */
void read_LWS_688(const CAN_message_t &imsg) {

	LWS_angle.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	LWS_speed.set_can_value((imsg.buf[2]));
	LWS_ok.set_can_value(((imsg.buf[3] & 0b00000001)));
	LWS_cal.set_can_value((((imsg.buf[3] & 0b00000010)) >> 1));
	LWS_trim.set_can_value((((imsg.buf[3] & 0b00000100)) >> 2));

}

/*
 * Decode a CAN frame for the message VCU_200
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_200(const CAN_message_t &imsg) {

	VCU_counterMsg200.set_can_value(((imsg.buf[0] & 0b00001111)));
	VCU_brakeLightCmd.set_can_value(((imsg.buf[1] & 0b00000001)));
	VCU_segmentHalf1Duty.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	VCU_segmentHalf2Duty.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message VCU_192
 * \param imsg A reference to the incoming CAN message frame
 */
void read_VCU_192(const CAN_message_t &imsg) {

	VCU_torqueCommand.set_can_value((imsg.buf[0]) | (imsg.buf[1] << 8));
	VCU_speedCommand.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	VCU_directionCommand.set_can_value(((imsg.buf[4] & 0b00000001)));
	VCU_inverterEnable.set_can_value(((imsg.buf[5] & 0b00000001)));
	VCU_inverterDischarge.set_can_value((((imsg.buf[5] & 0b00000010)) >> 1));
	VCU_speedModeEnable.set_can_value((((imsg.buf[5] & 0b00000100)) >> 2));
	VCU_counterMsg192.set_can_value((((imsg.buf[5] & 0b11110000)) >> 4));
	VCU_torqueLimitCommand.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PM_170
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PM_170(const CAN_message_t &imsg) {

	PM_vsmState.set_can_value((imsg.buf[0]));
	PM_pwmFrequency.set_can_value((imsg.buf[1]));
	PM_inverterState.set_can_value((imsg.buf[2]));
	PM_relayStatus1.set_can_value(((imsg.buf[3] & 0b00000001)));
	PM_relayStatus2.set_can_value((((imsg.buf[3] & 0b00000010)) >> 1));
	PM_relayStatus3.set_can_value((((imsg.buf[3] & 0b00000100)) >> 2));
	PM_relayStatus4.set_can_value((((imsg.buf[3] & 0b00001000)) >> 3));
	PM_relayStatus5.set_can_value((((imsg.buf[3] & 0b00010000)) >> 4));
	PM_relayStatus6.set_can_value((((imsg.buf[3] & 0b00100000)) >> 5));
	PM_inverterRunMode.set_can_value(((imsg.buf[4] & 0b00000001)));
	PM_inverterDischargeMode.set_can_value((((imsg.buf[4] & 0b11100000)) >> 5));
	PM_inverterCommandMode.set_can_value(((imsg.buf[5] & 0b00000001)));
	PM_counterMsg170.set_can_value((((imsg.buf[5] & 0b11110000)) >> 4));
	PM_inverterEnableState.set_can_value(((imsg.buf[6] & 0b00000001)));
	PM_startModeActive.set_can_value((((imsg.buf[6] & 0b01000000)) >> 6));
	PM_inverterEnableLockout.set_can_value((((imsg.buf[6] & 0b10000000)) >> 7));
	PM_directionCommand.set_can_value(((imsg.buf[7] & 0b00000001)));
	PM_bmsActive.set_can_value((((imsg.buf[7] & 0b00000010)) >> 1));
	PM_bmsTorqueLimiting.set_can_value((((imsg.buf[7] & 0b00000100)) >> 2));
	PM_maxSpeedLimiting.set_can_value((((imsg.buf[7] & 0b00001000)) >> 3));
	PM_lowSpeedLimiting.set_can_value((((imsg.buf[7] & 0b00100000)) >> 5));

}




/************************************************************************************

    Distribute incoming messages to the correct decoding functions

************************************************************************************/


/*
 * Decode a CAN message for the bus captured in raptor_CAN1.dbc.
 * To more efficiently allocate microcontroller resources, simply comment
 * out unnecessary messages that do not need to be decoded.
 * \param imsg A reference to the incoming CAN frame
 */
void decode_raptor_CAN1(const CAN_message_t &imsg) {

	switch (imsg.id) {

		case 201:
			read_VCU_201(imsg);
			break;

		case 402772111:
			read_DCDC_1801D08F(imsg);
			break;

		case 194:
			read_PM_194(imsg);
			break;

		case 176:
			read_PM_176(imsg);
			break;

		case 175:
			read_PM_175(imsg);
			break;

		case 174:
			read_PM_174(imsg);
			break;

		case 173:
			read_PM_173(imsg);
			break;

		case 172:
			read_PM_172(imsg);
			break;

		case 171:
			read_PM_171(imsg);
			break;

		case 169:
			read_PM_169(imsg);
			break;

		case 168:
			read_PM_168(imsg);
			break;

		case 167:
			read_PM_167(imsg);
			break;

		case 166:
			read_PM_166(imsg);
			break;

		case 165:
			read_PM_165(imsg);
			break;

		case 164:
			read_PM_164(imsg);
			break;

		case 163:
			read_PM_163(imsg);
			break;

		case 162:
			read_PM_162(imsg);
			break;

		case 161:
			read_PM_161(imsg);
			break;

		case 160:
			read_PM_160(imsg);
			break;

		case 193:
			read_VCU_193(imsg);
			break;

		case 402690000:
			read_VCU_18008FD0(imsg);
			break;

		case 454:
			read_C50_454(imsg);
			break;

		case 453:
			read_C50_453(imsg);
			break;

		case 452:
			read_C50_452(imsg);
			break;

		case 451:
			read_C50_451(imsg);
			break;

		case 450:
			read_C50_450(imsg);
			break;

		case 303:
			read_ATCC_303(imsg);
			break;

		case 302:
			read_ATCC_302(imsg);
			break;

		case 301:
			read_ATCC_301(imsg);
			break;

		case 300:
			read_ATCC_300(imsg);
			break;

		case 1984:
			read_LWS_1984(imsg);
			break;

		case 688:
			read_LWS_688(imsg);
			break;

		case 200:
			read_VCU_200(imsg);
			break;

		case 192:
			read_VCU_192(imsg);
			break;

		case 170:
			read_PM_170(imsg);
			break;

	}
}


#endif
