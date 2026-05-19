// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VSoC__pch.h"

//============================================================
// Constructors

VSoC::VSoC(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VSoC__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_uart_tx{vlSymsp->TOP.io_uart_tx}
    , io_uart_rx{vlSymsp->TOP.io_uart_rx}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VSoC::VSoC(const char* _vcname__)
    : VSoC(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VSoC::~VSoC() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VSoC___024root___eval_debug_assertions(VSoC___024root* vlSelf);
#endif  // VL_DEBUG
void VSoC___024root___eval_static(VSoC___024root* vlSelf);
void VSoC___024root___eval_initial(VSoC___024root* vlSelf);
void VSoC___024root___eval_settle(VSoC___024root* vlSelf);
void VSoC___024root___eval(VSoC___024root* vlSelf);

void VSoC::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VSoC::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VSoC___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VSoC___024root___eval_static(&(vlSymsp->TOP));
        VSoC___024root___eval_initial(&(vlSymsp->TOP));
        VSoC___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VSoC___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VSoC::eventsPending() { return false; }

uint64_t VSoC::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VSoC::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VSoC___024root___eval_final(VSoC___024root* vlSelf);

VL_ATTR_COLD void VSoC::final() {
    contextp()->executingFinal(true);
    VSoC___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VSoC::hierName() const { return vlSymsp->name(); }
const char* VSoC::modelName() const { return "VSoC"; }
unsigned VSoC::threads() const { return 1; }
void VSoC::prepareClone() const { contextp()->prepareClone(); }
void VSoC::atClone() const {
    contextp()->threadPoolpOnClone();
}
