#ifndef AFTERCOMMAND_HH
#define AFTERCOMMAND_HH

#include "Command.hh"
#include "EventListener.hh"
#include "Event.hh"
#include <memory>
#include <vector>

namespace openmsx {

class Reactor;
class EventDistributor;
class CommandController;
class AfterCmd;

class AfterCommand : public Command, private EventListener
{
public:
	typedef std::shared_ptr<const Event> EventPtr;

	AfterCommand(Reactor& reactor,
	             EventDistributor& eventDistributor,
	             CommandController& commandController);
	virtual ~AfterCommand();

	virtual void execute(array_ref<TclObject> tokens, TclObject& result);
	virtual std::string help(const std::vector<std::string>& tokens) const;
	virtual void tabCompletion(std::vector<std::string>& tokens) const;

private:
	template<typename PRED> void executeMatches(PRED pred);
	template<EventType T> void executeEvents();
	template<EventType T> void afterEvent(
	                   array_ref<TclObject> tokens, TclObject& result);
	void afterInputEvent(const EventPtr& event,
	                   array_ref<TclObject> tokens, TclObject& result);
	void afterTclTime (int ms,
	                   array_ref<TclObject> tokens, TclObject& result);
	void afterTime    (array_ref<TclObject> tokens, TclObject& result);
	void afterRealTime(array_ref<TclObject> tokens, TclObject& result);
	void afterIdle    (array_ref<TclObject> tokens, TclObject& result);
	void afterInfo    (array_ref<TclObject> tokens, TclObject& result);
	void afterCancel  (array_ref<TclObject> tokens, TclObject& result);

	// EventListener
	virtual int signalEvent(const std::shared_ptr<const Event>& event);

	typedef std::vector<std::unique_ptr<AfterCmd>> AfterCmds;
	AfterCmds afterCmds;
	Reactor& reactor;
	EventDistributor& eventDistributor;

	friend class AfterCmd;
	friend class AfterTimedCmd;
	friend class AfterRealTimeCmd;
};

} // namespace openmsx

#endif
