#include "StateMachine.hpp"

namespace Deus {
	StateMachine::StateMachine() {

	}
	StateMachine::~StateMachine() {

	}
	void StateMachine::pause() {

	}
	void StateMachine::AddState(StateRef newState, bool isReplacing) {
		this->_isAdding = true;
		this->_isReplacing = isReplacing;
		this->_newState = std::move(newState);
	}

	void StateMachine::RemoveState() {
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges() {
		if (this->_isRemoving && !this->_states.empty()) {
			this->_states.pop();

			if (!this->_states.empty()) {
				this->_states.top()->resume(); //TAKE FIRST OBJECT IN THE STACK AND RESUME IT. STACK IS LIKE ARRAY
			}
			this->_isRemoving = false;
		}

		if (this->_isAdding) {
			if (!this->_states.empty()) {
				if (this->_isReplacing) {
					this->_states.pop();
				}
				else {
					this->_states.top()->pause();
				}
			}

			this->_states.push(std::move(this->_newState));
			this->_states.top()->init();
			this->_isAdding = false;
		}
	}

	StateRef& StateMachine::GetActiveState() {
		return this->_states.top();
	}
}