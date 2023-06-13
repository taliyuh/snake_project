#ifndef STATEMAN_H
#define STATEMAN_H
#include "State.h"
#include <memory>
#include <stack>

namespace Engine{
class StateMan{
private:
    std::stack<std::unique_ptr<State>>m_stateStack;
    std::unique_ptr<State>m_newState;

    bool m_add;
    bool m_replace;
    bool m_remove;

public:
    StateMan();
    ~StateMan();

    void Add(std::unique_ptr<State> toAdd, bool replace = false);
    void PopCurrent();
    void ProcessStageChange();
    std::unique_ptr<State>& GetCurrent();
};
}

#endif // STATEMAN_H
