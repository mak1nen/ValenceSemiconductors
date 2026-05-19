// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSoC.h for the primary calling header

#include "VSoC__pch.h"

void VSoC___024root___ctor_var_reset(VSoC___024root* vlSelf);

VSoC___024root::VSoC___024root(VSoC__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    VSoC___024root___ctor_var_reset(this);
}

void VSoC___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VSoC___024root::~VSoC___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
