/**************************************************************************************************
// file:	Engine\Time\CAlarm.h
// A2DE
// Copyright (c) 2013 Blisspoint Softworks and Casey Ugone. All rights reserved.
// Contact cugone@gmail.com for questions or support.
// summary:	Declares the alarm class
 **************************************************************************************************/
#ifndef A2DE_CALARM_H
#define A2DE_CALARM_H

#include "../a2de_vals.h"
#include "ADTtime.h"
#include "CStopwatch.h"

A2DE_BEGIN

template<class FunctionObject>
class Alarm : public StopWatch {

public:

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="fn">The function object to run.</param>
     * <remarks>run_count is set to -1.</remarks>
     * <remarks>tickTime is set to 1.0.</remarks>
     **************************************************************************************************/
    Alarm(const FunctionObject& fn);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     * <param name="tickTime">Time in seconds between runs.</param>
     * <param name="fn">      The function object to run.</param>
     * <remarks>run_count is set to -1.</remarks>
     **************************************************************************************************/
    Alarm(double tickTime, const FunctionObject& fn);

    /**************************************************************************************************
     * <summary>Constructor.</summary>
     * <remarks>Casey Ugone, 12/14/2013.</remarks>
     * <param name="tickTime"> Time in seconds between runs.</param>
     * <param name="run_count">Number of runs where { run_count | -1 <= run_count <= INT_MAX }</param>
     * <remarks>A run_count of -1 denotes infinity.</remarks>
     * <param name="fn">       The function object to run.</param>
     **************************************************************************************************/
    Alarm(double tickTime, int run_count, const FunctionObject& fn);

    /**************************************************************************************************
     * <summary>Finaliser.</summary>
     * <remarks>Casey Ugone, 9/3/2012.</remarks>
     **************************************************************************************************/
    virtual ~Alarm();

    /**************************************************************************************************
     * <summary>Advances the alarm one tick.</summary>
     * <remarks>Casey Ugone, 12/20/2013.</remarks>
     * <remarks>If the alarm is not running, the method does nothing. If the run count reaches zero, the timer is reset but otherwise does nothing.
     * If the elapsed time passes, the function is run once and the timer is restarted.</remarks>
     * <returns>A copy of the function object.</returns>
     **************************************************************************************************/
    FunctionObject Tick();

protected:
    /// <summary> The delegate </summary>
    FunctionObject _delegate;
    /// <summary> Time of the tick </summary>
    double _tickTime;

    /// <summary> Number of runs </summary>
    int _run_count;

private:

};

A2DE_END

A2DE_BEGIN

template<class FunctionObject>
Alarm<FunctionObject>::Alarm(const FunctionObject& fn)
    : StopWatch(), _delegate(fn), _tickTime(1.0), _run_count(-1) { /* DO NOTHING */ }

template<class FunctionObject>
Alarm<FunctionObject>::Alarm(double tickTime, const FunctionObject& fn)
    : StopWatch(), _delegate(fn), _tickTime(tickTime), _run_count(-1) { /* DO NOTHING */ }

template<class FunctionObject>
Alarm<FunctionObject>::Alarm(double tickTime, int run_count, const FunctionObject& fn)
    : StopWatch(), _delegate(fn), _tickTime(tickTime), _run_count(run_count < -1 ? -1 : run_count) { /* DO NOTHING */ }

template<class FunctionObject>
Alarm<FunctionObject>::~Alarm() {
    if(_isRunning) Stop();
}

template<class FunctionObject>
FunctionObject Alarm<FunctionObject>::Tick() {
    if(IsRunning() == false) return _delegate;
    
    if(GetElapsedTimeInSeconds() >= _tickTime) {
        Reset();
        if(_run_count == 0) return _delegate;
        _delegate();
        if(_run_count > -1) --_run_count;
        Start();
    }
    return _delegate;
}

A2DE_END

#endif
