#pragma once

class AlarmEngine;

void InitAlarmThread(AlarmEngine& alarm);

#ifdef UNIT_TEST
void RunAlarmThreadForTest();
#endif