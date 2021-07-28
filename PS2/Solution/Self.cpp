#include <iostream>

using namespace std;

class State;

class StopWatch {

public:
	StopWatch();

	void start();

	void stop();

	void resume();

	void pause();

	void SetState(State* state);

private:
	State* mState;

};

class State {
public:
	virtual void Start(StopWatch* watch) {cout << "Start" << endl;}
	virtual void Stop(StopWatch* watch) {cout << "Stop" << endl;}
	virtual void Pause(StopWatch* watch) {cout << "Pause" << endl;}
	virtual void Resume(StopWatch* watch) {cout << "Resume" << endl;}

	void ChangeState(StopWatch* watch, State* state)
	{
		watch->SetState(state);
	}
};

class WatchStarted : public State {
public:
	void Pause(StopWatch* watch) override;

	void Stop(StopWatch* watch) override;

	static State* Get();

};

class WatchStopped : public State {
public:
	void Start(StopWatch* watch) override;

	static State* Get();
};

class WatchPaused : public State {
public:
	void Resume(StopWatch* watch) override;

	void Stop(StopWatch* watch) override;

	static State* Get();
};


StopWatch::StopWatch()
: mState (WatchStopped::Get())
{
}

void StopWatch::start()
{
	// logic
	mState->Start(this);
}


void StopWatch::stop()
{
	// logic
	mState->Stop(this);
}

void StopWatch::resume()
{
	// logic
	mState->Resume(this);
}

void StopWatch::pause()
{
	// logic
	mState->Pause(this);
}

void StopWatch::SetState(State* state)
{
	mState = state;
}


// ----------------------------------------------------------------
// WatchStarted methods
// ----------------------------------------------------------------
void WatchStarted::Pause(StopWatch* watch)
{
	ChangeState(watch, WatchPaused::Get());
}

void WatchStarted::Stop(StopWatch* watch)
{
	ChangeState(watch, WatchStopped::Get());
}

State* WatchStarted::Get()
{
	static WatchStarted watchStarted;
	return &watchStarted;
}
// ----------------------------------------------------------------


// ----------------------------------------------------------------
// WatchStopped methods
// ----------------------------------------------------------------
void WatchStopped::Start(StopWatch* watch)
{
	ChangeState(watch, WatchStarted::Get());
}

State* WatchStopped::Get()
{
	static WatchStopped watchStopped;
	return &watchStopped;
}
// ----------------------------------------------------------------


// ----------------------------------------------------------------
// WatchPaused methods
// ----------------------------------------------------------------
void WatchPaused::Resume(StopWatch* watch)
{
	ChangeState(watch, WatchStarted::Get());
}

void WatchPaused::Stop(StopWatch* watch)
{
	ChangeState(watch, WatchStopped::Get());
}

State* WatchPaused::Get()
{
	static WatchPaused watchPaused;
	return &watchPaused;
}
// ----------------------------------------------------------------



int main()
{
	StopWatch watch;
	watch.start();
	watch.start(); // extra start
	watch.resume(); // false resume

	watch.pause();

	watch.stop();

	watch.pause(); //false pause
	return 0;
}
