// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSoC.h for the primary calling header

#include "VSoC__pch.h"

void VSoC___024root___eval_triggers_vec__act(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_triggers_vec__act\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clock) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
}

bool VSoC___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlWide<8>/*255:0*/ VSoC__ConstPool__CONST_h95b5ef3e_0;

void VSoC___024root___nba_sequent__TOP__0(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___nba_sequent__TOP__0\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ SoC__DOT__sram_io_valid;
    SoC__DOT__sram_io_valid = 0;
    CData/*7:0*/ SoC__DOT___core_io_dcache_wstrb;
    SoC__DOT___core_io_dcache_wstrb = 0;
    CData/*0:0*/ SoC__DOT___core_io_dcache_valid;
    SoC__DOT___core_io_dcache_valid = 0;
    CData/*0:0*/ SoC__DOT__sram_sel;
    SoC__DOT__sram_sel = 0;
    CData/*0:0*/ SoC__DOT__uart_write;
    SoC__DOT__uart_write = 0;
    QData/*63:0*/ SoC__DOT____Vcellinp__core__io_dcache_rdata;
    SoC__DOT____Vcellinp__core__io_dcache_rdata = 0;
    CData/*0:0*/ SoC__DOT____Vcellinp__sram__io_wen;
    SoC__DOT____Vcellinp__sram__io_wen = 0;
    QData/*63:0*/ SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2;
    SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 = 0;
    QData/*63:0*/ SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1;
    SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 = 0;
    CData/*0:0*/ SoC__DOT__core__DOT__execute__DOT__bu__DOT___io_taken_T_7;
    SoC__DOT__core__DOT__execute__DOT__bu__DOT___io_taken_T_7 = 0;
    VlWide<4>/*126:0*/ SoC__DOT__core__DOT__memory__DOT__shiftedStoreData;
    VL_ZERO_W(127, SoC__DOT__core__DOT__memory__DOT__shiftedStoreData);
    QData/*63:0*/ SoC__DOT__core__DOT__memory__DOT__shiftedLoad;
    SoC__DOT__core__DOT__memory__DOT__shiftedLoad = 0;
    CData/*0:0*/ __VdfgRegularize_hebeb780c_0_2;
    __VdfgRegularize_hebeb780c_0_2 = 0;
    CData/*0:0*/ __VdfgRegularize_hebeb780c_0_12;
    __VdfgRegularize_hebeb780c_0_12 = 0;
    QData/*63:0*/ __Vdly__SoC__DOT__core__DOT__frontend__DOT__pc;
    __Vdly__SoC__DOT__core__DOT__frontend__DOT__pc = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__core__DOT__if_id__DOT__reg_valid;
    __Vdly__SoC__DOT__core__DOT__if_id__DOT__reg_valid = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isStore;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isStore = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJal;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJal = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_valid;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_valid = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_0;
    __Vdly__SoC__DOT__dcache__DOT__valid_0 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_1;
    __Vdly__SoC__DOT__dcache__DOT__valid_1 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_2;
    __Vdly__SoC__DOT__dcache__DOT__valid_2 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_3;
    __Vdly__SoC__DOT__dcache__DOT__valid_3 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_4;
    __Vdly__SoC__DOT__dcache__DOT__valid_4 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_5;
    __Vdly__SoC__DOT__dcache__DOT__valid_5 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_6;
    __Vdly__SoC__DOT__dcache__DOT__valid_6 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_7;
    __Vdly__SoC__DOT__dcache__DOT__valid_7 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_8;
    __Vdly__SoC__DOT__dcache__DOT__valid_8 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_9;
    __Vdly__SoC__DOT__dcache__DOT__valid_9 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_10;
    __Vdly__SoC__DOT__dcache__DOT__valid_10 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_11;
    __Vdly__SoC__DOT__dcache__DOT__valid_11 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_12;
    __Vdly__SoC__DOT__dcache__DOT__valid_12 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_13;
    __Vdly__SoC__DOT__dcache__DOT__valid_13 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_14;
    __Vdly__SoC__DOT__dcache__DOT__valid_14 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_15;
    __Vdly__SoC__DOT__dcache__DOT__valid_15 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_16;
    __Vdly__SoC__DOT__dcache__DOT__valid_16 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_17;
    __Vdly__SoC__DOT__dcache__DOT__valid_17 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_18;
    __Vdly__SoC__DOT__dcache__DOT__valid_18 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_19;
    __Vdly__SoC__DOT__dcache__DOT__valid_19 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_20;
    __Vdly__SoC__DOT__dcache__DOT__valid_20 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_21;
    __Vdly__SoC__DOT__dcache__DOT__valid_21 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_22;
    __Vdly__SoC__DOT__dcache__DOT__valid_22 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_23;
    __Vdly__SoC__DOT__dcache__DOT__valid_23 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_24;
    __Vdly__SoC__DOT__dcache__DOT__valid_24 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_25;
    __Vdly__SoC__DOT__dcache__DOT__valid_25 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_26;
    __Vdly__SoC__DOT__dcache__DOT__valid_26 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_27;
    __Vdly__SoC__DOT__dcache__DOT__valid_27 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_28;
    __Vdly__SoC__DOT__dcache__DOT__valid_28 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_29;
    __Vdly__SoC__DOT__dcache__DOT__valid_29 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_30;
    __Vdly__SoC__DOT__dcache__DOT__valid_30 = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__dcache__DOT__valid_31;
    __Vdly__SoC__DOT__dcache__DOT__valid_31 = 0;
    CData/*1:0*/ __Vdly__SoC__DOT__uart__DOT__state;
    __Vdly__SoC__DOT__uart__DOT__state = 0;
    SData/*8:0*/ __Vdly__SoC__DOT__uart__DOT__baud_cnt;
    __Vdly__SoC__DOT__uart__DOT__baud_cnt = 0;
    CData/*3:0*/ __Vdly__SoC__DOT__uart__DOT__bit_cnt;
    __Vdly__SoC__DOT__uart__DOT__bit_cnt = 0;
    CData/*7:0*/ __Vdly__SoC__DOT__uart__DOT__shift_reg;
    __Vdly__SoC__DOT__uart__DOT__shift_reg = 0;
    CData/*0:0*/ __Vdly__SoC__DOT__uart__DOT__tx_reg;
    __Vdly__SoC__DOT__uart__DOT__tx_reg = 0;
    QData/*63:0*/ __VdlyVal__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0;
    __VdlyVal__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0 = 0;
    SData/*12:0*/ __VdlyDim0__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0;
    __VdlyDim0__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0 = 0;
    CData/*0:0*/ __VdlySet__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0;
    __VdlySet__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0 = 0;
    QData/*63:0*/ __VdlyVal__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0;
    __VdlyVal__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0 = 0;
    SData/*12:0*/ __VdlyDim0__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0;
    __VdlyDim0__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0 = 0;
    CData/*0:0*/ __VdlySet__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0;
    __VdlySet__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0 = 0;
    VlWide<8>/*255:0*/ __Vtemp_3;
    VlWide<8>/*255:0*/ __Vtemp_6;
    VlWide<4>/*127:0*/ __Vtemp_32;
    VlWide<4>/*127:0*/ __Vtemp_33;
    VlWide<32>/*1023:0*/ __Vtemp_43;
    VlWide<27>/*863:0*/ __Vtemp_58;
    VlWide<27>/*863:0*/ __Vtemp_73;
    VlWide<53>/*1695:0*/ __Vtemp_74;
    VlWide<64>/*2047:0*/ __Vtemp_105;
    VlWide<16>/*511:0*/ __Vtemp_113;
    // Body
    __Vdly__SoC__DOT__core__DOT__if_id__DOT__reg_valid 
        = vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_valid;
    __Vdly__SoC__DOT__uart__DOT__baud_cnt = vlSelfRef.SoC__DOT__uart__DOT__baud_cnt;
    __Vdly__SoC__DOT__uart__DOT__bit_cnt = vlSelfRef.SoC__DOT__uart__DOT__bit_cnt;
    __Vdly__SoC__DOT__uart__DOT__shift_reg = vlSelfRef.SoC__DOT__uart__DOT__shift_reg;
    __Vdly__SoC__DOT__uart__DOT__tx_reg = vlSelfRef.SoC__DOT__uart__DOT__tx_reg;
    __Vdly__SoC__DOT__uart__DOT__state = vlSelfRef.SoC__DOT__uart__DOT__state;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_valid 
        = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isStore 
        = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isStore;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad 
        = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJal 
        = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJal;
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr 
        = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr;
    __VdlySet__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0 = 0U;
    __Vdly__SoC__DOT__core__DOT__frontend__DOT__pc 
        = vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc;
    __VdlySet__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0 = 0U;
    __Vdly__SoC__DOT__dcache__DOT__valid_0 = vlSelfRef.SoC__DOT__dcache__DOT__valid_0;
    __Vdly__SoC__DOT__dcache__DOT__valid_1 = vlSelfRef.SoC__DOT__dcache__DOT__valid_1;
    __Vdly__SoC__DOT__dcache__DOT__valid_2 = vlSelfRef.SoC__DOT__dcache__DOT__valid_2;
    __Vdly__SoC__DOT__dcache__DOT__valid_3 = vlSelfRef.SoC__DOT__dcache__DOT__valid_3;
    __Vdly__SoC__DOT__dcache__DOT__valid_4 = vlSelfRef.SoC__DOT__dcache__DOT__valid_4;
    __Vdly__SoC__DOT__dcache__DOT__valid_5 = vlSelfRef.SoC__DOT__dcache__DOT__valid_5;
    __Vdly__SoC__DOT__dcache__DOT__valid_6 = vlSelfRef.SoC__DOT__dcache__DOT__valid_6;
    __Vdly__SoC__DOT__dcache__DOT__valid_7 = vlSelfRef.SoC__DOT__dcache__DOT__valid_7;
    __Vdly__SoC__DOT__dcache__DOT__valid_8 = vlSelfRef.SoC__DOT__dcache__DOT__valid_8;
    __Vdly__SoC__DOT__dcache__DOT__valid_9 = vlSelfRef.SoC__DOT__dcache__DOT__valid_9;
    __Vdly__SoC__DOT__dcache__DOT__valid_10 = vlSelfRef.SoC__DOT__dcache__DOT__valid_10;
    __Vdly__SoC__DOT__dcache__DOT__valid_11 = vlSelfRef.SoC__DOT__dcache__DOT__valid_11;
    __Vdly__SoC__DOT__dcache__DOT__valid_12 = vlSelfRef.SoC__DOT__dcache__DOT__valid_12;
    __Vdly__SoC__DOT__dcache__DOT__valid_13 = vlSelfRef.SoC__DOT__dcache__DOT__valid_13;
    __Vdly__SoC__DOT__dcache__DOT__valid_14 = vlSelfRef.SoC__DOT__dcache__DOT__valid_14;
    __Vdly__SoC__DOT__dcache__DOT__valid_15 = vlSelfRef.SoC__DOT__dcache__DOT__valid_15;
    __Vdly__SoC__DOT__dcache__DOT__valid_16 = vlSelfRef.SoC__DOT__dcache__DOT__valid_16;
    __Vdly__SoC__DOT__dcache__DOT__valid_17 = vlSelfRef.SoC__DOT__dcache__DOT__valid_17;
    __Vdly__SoC__DOT__dcache__DOT__valid_18 = vlSelfRef.SoC__DOT__dcache__DOT__valid_18;
    __Vdly__SoC__DOT__dcache__DOT__valid_19 = vlSelfRef.SoC__DOT__dcache__DOT__valid_19;
    __Vdly__SoC__DOT__dcache__DOT__valid_20 = vlSelfRef.SoC__DOT__dcache__DOT__valid_20;
    __Vdly__SoC__DOT__dcache__DOT__valid_21 = vlSelfRef.SoC__DOT__dcache__DOT__valid_21;
    __Vdly__SoC__DOT__dcache__DOT__valid_22 = vlSelfRef.SoC__DOT__dcache__DOT__valid_22;
    __Vdly__SoC__DOT__dcache__DOT__valid_23 = vlSelfRef.SoC__DOT__dcache__DOT__valid_23;
    __Vdly__SoC__DOT__dcache__DOT__valid_24 = vlSelfRef.SoC__DOT__dcache__DOT__valid_24;
    __Vdly__SoC__DOT__dcache__DOT__valid_25 = vlSelfRef.SoC__DOT__dcache__DOT__valid_25;
    __Vdly__SoC__DOT__dcache__DOT__valid_26 = vlSelfRef.SoC__DOT__dcache__DOT__valid_26;
    __Vdly__SoC__DOT__dcache__DOT__valid_27 = vlSelfRef.SoC__DOT__dcache__DOT__valid_27;
    __Vdly__SoC__DOT__dcache__DOT__valid_28 = vlSelfRef.SoC__DOT__dcache__DOT__valid_28;
    __Vdly__SoC__DOT__dcache__DOT__valid_29 = vlSelfRef.SoC__DOT__dcache__DOT__valid_29;
    __Vdly__SoC__DOT__dcache__DOT__valid_30 = vlSelfRef.SoC__DOT__dcache__DOT__valid_30;
    __Vdly__SoC__DOT__dcache__DOT__valid_31 = vlSelfRef.SoC__DOT__dcache__DOT__valid_31;
    __Vdly__SoC__DOT__core__DOT__if_id__DOT__reg_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (1U 
                                                   & ((~ (IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush)) 
                                                      & ((IData)(vlSelfRef.SoC__DOT__core__DOT__pipe_stall)
                                                          ? (IData)(vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_valid)
                                                          : 
                                                         (~ (IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush))))));
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid)
                                                       : 
                                                      ((~ (IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_stall)) 
                                                       & (IData)(vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_valid)))));
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isStore 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isStore)
                                                       : 
                                                      (0x23U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))));
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_useImm 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_useImm)
                                                       : 
                                                      ((0x13U 
                                                        == 
                                                        (0x0000007fU 
                                                         & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                       | ((3U 
                                                           == 
                                                           (0x0000007fU 
                                                            & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                          | ((0x67U 
                                                              == 
                                                              (0x0000007fU 
                                                               & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                             | (0x23U 
                                                                == 
                                                                (0x0000007fU 
                                                                 & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr))))))));
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad)
                                                       : 
                                                      (3U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))));
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLui 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLui)
                                                       : 
                                                      (0x37U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))));
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isAuipc 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isAuipc)
                                                       : 
                                                      (0x17U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))));
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isBranch 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isBranch)
                                                       : 
                                                      (0x63U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))));
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJal 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJal)
                                                       : 
                                                      (0x6fU 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))));
    __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)
                                                       ? (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr)
                                                       : 
                                                      (0x67U 
                                                       == 
                                                       (0x0000007fU 
                                                        & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))));
    if (vlSelfRef.SoC__DOT__sram__DOT___GEN) {
        __VdlyVal__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0 
            = vlSelfRef.SoC__DOT__sram__DOT__mergedWord;
        __VdlyDim0__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0 
            = (0x00001fffU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                      >> 3U)));
        __VdlySet__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0 = 1U;
        __VdlyVal__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0 
            = vlSelfRef.SoC__DOT__sram__DOT__mergedWord;
        __VdlyDim0__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0 
            = (0x00001fffU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                      >> 3U)));
        __VdlySet__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0 = 1U;
    }
    vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (~ (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)) 
                                                   & (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_valid)));
    if (vlSelfRef.reset) {
        __Vdly__SoC__DOT__uart__DOT__state = 0U;
        __Vdly__SoC__DOT__uart__DOT__baud_cnt = 0U;
        __Vdly__SoC__DOT__uart__DOT__bit_cnt = 0U;
        __Vdly__SoC__DOT__uart__DOT__shift_reg = 0U;
        __Vdly__SoC__DOT__uart__DOT__tx_reg = 1U;
        __Vdly__SoC__DOT__core__DOT__frontend__DOT__pc = 0x0000000000001000ULL;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp = 0U;
        vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad = 0U;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_brOp = 0U;
        vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp = 0U;
        vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_0 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_1 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_2 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_3 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_4 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_5 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_6 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_7 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_8 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_9 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_10 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_11 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_12 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_13 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_14 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_15 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_16 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_17 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_18 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_19 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_20 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_21 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_22 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_23 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_24 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_25 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_26 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_27 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_28 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_29 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_30 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_31 = 0ULL;
        __Vdly__SoC__DOT__dcache__DOT__valid_0 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_1 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_2 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_3 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_4 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_5 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_6 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_7 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_8 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_9 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_10 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_11 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_12 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_13 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_14 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_15 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_16 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_17 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_18 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_19 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_20 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_21 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_22 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_23 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_24 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_25 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_26 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_27 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_28 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_29 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_30 = 0U;
        __Vdly__SoC__DOT__dcache__DOT__valid_31 = 0U;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_0 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_1 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_2 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_3 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_4 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_5 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_6 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_7 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_8 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_9 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_10 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_11 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_12 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_13 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_14 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_15 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_16 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_17 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_18 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_19 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_20 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_21 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_22 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_23 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_24 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_25 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_26 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_27 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_28 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_29 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_30 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__tags_31 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_0 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_1 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_2 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_3 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_4 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_5 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_6 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_7 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_8 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_9 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_10 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_11 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_12 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_13 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_14 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_15 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_16 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_17 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_18 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_19 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_20 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_21 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_22 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_23 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_24 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_25 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_26 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_27 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_28 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_29 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_30 = 0ULL;
        vlSelfRef.SoC__DOT__dcache__DOT__data_31 = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_pc = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_memOp = 0U;
        vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_valid = 0U;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd = 0U;
        vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore = 0U;
        vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result = 0ULL;
        vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rd = 0U;
        vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd = 0U;
        vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr = 0U;
    } else {
        vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN 
            = (1U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state));
        vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0 
            = (0x01b1U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__baud_cnt));
        vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_1 
            = (2U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state));
        vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_2 
            = (7U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__bit_cnt));
        vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_3 
            = ((((((3U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
                   & (IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0))
                   ? 0U : (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
                 << 6U) | ((((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0) 
                             & (IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_2))
                             ? 3U : (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
                           << 4U)) | ((((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0)
                                         ? 2U : (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
                                       << 2U) | ((IData)(vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_valid)
                                                  ? 1U
                                                  : (IData)(vlSelfRef.SoC__DOT__uart__DOT__state))));
        __Vdly__SoC__DOT__uart__DOT__state = (3U & 
                                              ((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_3) 
                                               >> (7U 
                                                   & VL_SHIFTL_III(3,32,32, (IData)(vlSelfRef.SoC__DOT__uart__DOT__state), 1U))));
        vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_4 
            = (((QData)((IData)(((((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0)
                                    ? 0U : (0x000001ffU 
                                            & ((IData)(1U) 
                                               + (IData)(vlSelfRef.SoC__DOT__uart__DOT__baud_cnt)))) 
                                  << 9U) | ((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0)
                                             ? 0U : 
                                            (0x000001ffU 
                                             & ((IData)(1U) 
                                                + (IData)(vlSelfRef.SoC__DOT__uart__DOT__baud_cnt))))))) 
                << 0x00000012U) | (QData)((IData)((
                                                   (((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0)
                                                      ? 0U
                                                      : 
                                                     (0x000001ffU 
                                                      & ((IData)(1U) 
                                                         + (IData)(vlSelfRef.SoC__DOT__uart__DOT__baud_cnt)))) 
                                                    << 9U) 
                                                   | ((IData)(vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_valid)
                                                       ? 0U
                                                       : (IData)(vlSelfRef.SoC__DOT__uart__DOT__baud_cnt))))));
        __Vdly__SoC__DOT__uart__DOT__baud_cnt = ((0x23U 
                                                  >= 
                                                  (0x0000003fU 
                                                   & ((IData)(9U) 
                                                      * (IData)(vlSelfRef.SoC__DOT__uart__DOT__state))))
                                                  ? 
                                                 (0x000001ffU 
                                                  & (IData)(
                                                            (vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_4 
                                                             >> 
                                                             (0x0000003fU 
                                                              & ((IData)(9U) 
                                                                 * (IData)(vlSelfRef.SoC__DOT__uart__DOT__state))))))
                                                  : 0U);
        if ((0U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state))) {
            if (vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_valid) {
                __Vdly__SoC__DOT__uart__DOT__shift_reg 
                    = vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_data;
            }
        } else {
            vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT__unnamedblk2__DOT___GEN_5 
                = ((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_1) 
                   & (IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0));
            if (vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN) {
                if (vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_0) {
                    __Vdly__SoC__DOT__uart__DOT__bit_cnt = 0U;
                }
            } else if ((1U & (~ ((~ (IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT__unnamedblk2__DOT___GEN_5)) 
                                 | (IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_2))))) {
                __Vdly__SoC__DOT__uart__DOT__bit_cnt 
                    = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.SoC__DOT__uart__DOT__bit_cnt)));
            }
            if ((1U & (~ ((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN) 
                          | (~ (IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT__unnamedblk2__DOT___GEN_5)))))) {
                __Vdly__SoC__DOT__uart__DOT__shift_reg 
                    = (0x0000007fU & ((IData)(vlSelfRef.SoC__DOT__uart__DOT__shift_reg) 
                                      >> 1U));
            }
        }
        __Vdly__SoC__DOT__uart__DOT__tx_reg = (1U & 
                                               ((0U 
                                                 == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
                                                | ((~ (IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN)) 
                                                   & ((IData)(vlSelfRef.SoC__DOT__uart__DOT__unnamedblk1__DOT___GEN_1)
                                                       ? (IData)(vlSelfRef.SoC__DOT__uart__DOT__shift_reg)
                                                       : 
                                                      ((3U 
                                                        == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
                                                       | (IData)(vlSelfRef.SoC__DOT__uart__DOT__tx_reg))))));
        if (vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush) {
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc = 0ULL;
        } else if ((1U & (~ (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)))) {
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc 
                = vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_pc;
        }
        if ((1U & (~ (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)))) {
            vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad 
                = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad;
            vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp 
                = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_memOp;
            vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val 
                = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val;
        }
        vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0 
            = ((IData)(vlSelfRef.SoC__DOT__core__DOT___writeback_io_wen) 
               & (0U != (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)));
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_0 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (1U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_1 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (2U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_2 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (3U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_3 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (4U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_4 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (5U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_5 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (6U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_6 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (7U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_7 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (8U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_8 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (9U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_9 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x0aU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_10 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x0bU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_11 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x0cU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_12 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x0dU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_13 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x0eU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_14 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x0fU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_15 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x10U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_16 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x11U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_17 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x12U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_18 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x13U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_19 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x14U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_20 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x15U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_21 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x16U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_22 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x17U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_23 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x18U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_24 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x19U == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_25 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1aU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_26 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1bU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_27 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1cU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_28 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1dU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_29 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x1eU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_30 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        if (((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__unnamedblk1__DOT___GEN_0) 
             & (0x0000001fU == (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)))) {
            vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_31 
                = vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result;
        }
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_2 
            = (0U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_4 
            = (1U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_6 
            = (2U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_8 
            = (3U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_10 
            = (4U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_12 
            = (5U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_14 
            = (6U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_16 
            = (7U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_18 
            = (8U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_20 
            = (9U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                             >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_22 
            = (0x0aU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_24 
            = (0x0bU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_26 
            = (0x0cU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_28 
            = (0x0dU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_30 
            = (0x0eU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_32 
            = (0x0fU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_34 
            = (0x10U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_36 
            = (0x11U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_38 
            = (0x12U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_40 
            = (0x13U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_42 
            = (0x14U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_44 
            = (0x15U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_46 
            = (0x16U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_48 
            = (0x17U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_50 
            = (0x18U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_52 
            = (0x19U == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_54 
            = (0x1aU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_56 
            = (0x1bU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_58 
            = (0x1cU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_60 
            = (0x1dU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_62 
            = (0x1eU == (0x0000001fU & (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                >> 6U))));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65 
            = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__hit) 
               & (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_3 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_2));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_5 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_4));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_7 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_6));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_9 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_8));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_11 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_10));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_13 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_12));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_15 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_14));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_17 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_16));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_19 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_18));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_21 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_20));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_23 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_22));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_25 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_24));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_27 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_26));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_29 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_28));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_31 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_30));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_33 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_32));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_35 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_34));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_37 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_36));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_39 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_38));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_41 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_40));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_43 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_42));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_45 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_44));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_47 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_46));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_49 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_48));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_51 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_50));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_53 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_52));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_55 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_54));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_57 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_56));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_59 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_58));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_61 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_60));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_63 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_62));
        vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_64 
            = ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid) 
               & (0x00000000000007c0ULL == (0x00000000000007c0ULL 
                                            & vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result)));
        __Vdly__SoC__DOT__dcache__DOT__valid_0 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_3) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_0));
        __Vdly__SoC__DOT__dcache__DOT__valid_1 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_5) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_1));
        __Vdly__SoC__DOT__dcache__DOT__valid_2 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_7) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_2));
        __Vdly__SoC__DOT__dcache__DOT__valid_3 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_9) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_3));
        __Vdly__SoC__DOT__dcache__DOT__valid_4 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_11) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_4));
        __Vdly__SoC__DOT__dcache__DOT__valid_5 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_13) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_5));
        __Vdly__SoC__DOT__dcache__DOT__valid_6 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_15) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_6));
        __Vdly__SoC__DOT__dcache__DOT__valid_7 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_17) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_7));
        __Vdly__SoC__DOT__dcache__DOT__valid_8 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_19) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_8));
        __Vdly__SoC__DOT__dcache__DOT__valid_9 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_21) 
                                                  | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_9));
        __Vdly__SoC__DOT__dcache__DOT__valid_10 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_23) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_10));
        __Vdly__SoC__DOT__dcache__DOT__valid_11 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_25) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_11));
        __Vdly__SoC__DOT__dcache__DOT__valid_12 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_27) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_12));
        __Vdly__SoC__DOT__dcache__DOT__valid_13 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_29) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_13));
        __Vdly__SoC__DOT__dcache__DOT__valid_14 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_31) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_14));
        __Vdly__SoC__DOT__dcache__DOT__valid_15 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_33) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_15));
        __Vdly__SoC__DOT__dcache__DOT__valid_16 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_35) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_16));
        __Vdly__SoC__DOT__dcache__DOT__valid_17 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_37) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_17));
        __Vdly__SoC__DOT__dcache__DOT__valid_18 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_39) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_18));
        __Vdly__SoC__DOT__dcache__DOT__valid_19 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_41) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_19));
        __Vdly__SoC__DOT__dcache__DOT__valid_20 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_43) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_20));
        __Vdly__SoC__DOT__dcache__DOT__valid_21 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_45) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_21));
        __Vdly__SoC__DOT__dcache__DOT__valid_22 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_47) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_22));
        __Vdly__SoC__DOT__dcache__DOT__valid_23 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_49) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_23));
        __Vdly__SoC__DOT__dcache__DOT__valid_24 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_51) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_24));
        __Vdly__SoC__DOT__dcache__DOT__valid_25 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_53) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_25));
        __Vdly__SoC__DOT__dcache__DOT__valid_26 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_55) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_26));
        __Vdly__SoC__DOT__dcache__DOT__valid_27 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_57) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_27));
        __Vdly__SoC__DOT__dcache__DOT__valid_28 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_59) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_28));
        __Vdly__SoC__DOT__dcache__DOT__valid_29 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_61) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_29));
        __Vdly__SoC__DOT__dcache__DOT__valid_30 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_63) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_30));
        __Vdly__SoC__DOT__dcache__DOT__valid_31 = ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_64) 
                                                   | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_31));
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_3) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_0 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_5) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_1 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_7) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_2 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_9) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_3 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_11) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_4 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_13) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_5 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_15) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_6 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_17) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_19) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_8 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_21) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_9 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_23) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_10 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_25) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_11 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_27) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_12 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_29) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_13 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_31) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_33) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_35) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_16 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_37) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_17 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_39) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_18 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_41) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_19 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_43) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_20 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_45) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_21 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_47) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_49) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_51) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_24 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_53) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_55) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_57) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_59) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_61) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_63) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_64) {
            vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                   >> 0x0bU);
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_2))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_0 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_3) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_0 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_4))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_1 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_5) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_1 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_6))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_2 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_7) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_2 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_8))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_3 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_9) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_3 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_10))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_4 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_11) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_4 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_12))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_5 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_13) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_5 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_14))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_6 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_15) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_6 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_16))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_7 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_17) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_7 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_18))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_8 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_19) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_8 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_20))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_9 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_21) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_9 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_22))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_10 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_23) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_10 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_24))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_11 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_25) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_11 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_26))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_12 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_27) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_12 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_28))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_13 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_29) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_13 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_30))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_14 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_31) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_14 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_32))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_15 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_33) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_15 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_34))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_16 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_35) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_16 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_36))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_17 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_37) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_17 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_38))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_18 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_39) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_18 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_40))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_19 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_41) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_19 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_42))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_20 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_43) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_20 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_44))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_21 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_45) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_21 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_46))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_22 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_47) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_22 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_48))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_23 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_49) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_23 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_50))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_24 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_51) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_24 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_52))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_25 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_53) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_25 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_54))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_26 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_55) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_26 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_56))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_27 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_57) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_27 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_58))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_28 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_59) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_28 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_60))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_29 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_61) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_29 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_62))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_30 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_63) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_30 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        if (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_65) 
             & (0x00000000000007c0ULL == (0x00000000000007c0ULL 
                                          & vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result)))) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_31 
                = vlSelfRef.SoC__DOT___core_io_dcache_wdata;
        } else if (vlSelfRef.SoC__DOT__dcache__DOT__unnamedblk1__DOT___GEN_64) {
            vlSelfRef.SoC__DOT__dcache__DOT__data_31 
                = vlSelfRef.SoC__DOT___sram_io_rdata;
        }
        vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd 
            = vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rd;
        if ((1U & (~ (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)))) {
            vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_valid 
                = vlSelfRef.SoC__DOT__core__DOT____Vcellinp__forward__io_ex_wen;
            vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore 
                = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isStore) 
                   & (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid));
            vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                = vlSelfRef.SoC__DOT__core__DOT___execute_io_out_result;
            vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rd 
                = vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd;
        }
        if (vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush) {
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp = 0U;
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_brOp = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)))) {
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp 
                = (((IData)((0x40000033U == (0xfe00707fU 
                                             & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)))
                     ? 1U : ((IData)(((0x00007000U 
                                       == (0x00007000U 
                                           & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                      & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))
                              ? 2U : ((IData)(((0x00006000U 
                                                == 
                                                (0x00007000U 
                                                 & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                               & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))
                                       ? 3U : ((IData)(
                                                       ((0x00004000U 
                                                         == 
                                                         (0x00007000U 
                                                          & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                        & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))
                                                ? 4U
                                                : ((IData)(
                                                           ((0x00001000U 
                                                             == 
                                                             (0x00007000U 
                                                              & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                            & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))
                                                    ? 5U
                                                    : 
                                                   (((0U 
                                                      == 
                                                      (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                       >> 0x00000019U)) 
                                                     & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_13))
                                                     ? 6U
                                                     : 
                                                    (((0x20U 
                                                       == 
                                                       (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                        >> 0x00000019U)) 
                                                      & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_13))
                                                      ? 7U
                                                      : 
                                                     ((IData)(
                                                              ((0x00002000U 
                                                                == 
                                                                (0x00007000U 
                                                                 & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                               & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))
                                                       ? 8U
                                                       : 
                                                      (9U 
                                                       & (- (IData)((IData)(
                                                                            ((0x00003000U 
                                                                              == 
                                                                              (0x00007000U 
                                                                               & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                                             & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))))))))))))) 
                   & (- (IData)((1U & (~ (IData)(vlSelfRef.SoC__DOT__core__DOT__decode__DOT___GEN))))));
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_brOp 
                = (7U & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                         >> 0x0000000cU));
        }
        if (vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush) {
            __Vdly__SoC__DOT__core__DOT__frontend__DOT__pc 
                = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJal)
                    ? vlSelfRef.SoC__DOT__core__DOT__execute__DOT___bu_io_target
                    : ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr)
                        ? (0xfffffffffffffffeULL & 
                           (vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val 
                            + vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm))
                        : vlSelfRef.SoC__DOT__core__DOT__execute__DOT___bu_io_target));
        } else if ((1U & (~ (IData)(vlSelfRef.SoC__DOT__core__DOT__pipe_stall)))) {
            __Vdly__SoC__DOT__core__DOT__frontend__DOT__pc 
                = (4ULL + vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc);
        }
        if (vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush) {
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm = 0ULL;
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val = 0ULL;
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_memOp = 0U;
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val = 0ULL;
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall)))) {
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm 
                = (((QData)((IData)((- (IData)((vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                >> 0x0000001fU))))) 
                    << 0x00000020U) | (QData)((IData)(
                                                      ((0x23U 
                                                        == 
                                                        (0x0000007fU 
                                                         & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr))
                                                        ? 
                                                       (((- (IData)(
                                                                    (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                     >> 0x0000001fU))) 
                                                         << 0x0000000cU) 
                                                        | ((0x00000fe0U 
                                                            & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                               >> 0x00000014U)) 
                                                           | (0x0000001fU 
                                                              & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                 >> 7U))))
                                                        : 
                                                       ((0x63U 
                                                         == 
                                                         (0x0000007fU 
                                                          & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr))
                                                         ? 
                                                        (((- (IData)(
                                                                     (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                      >> 0x0000001fU))) 
                                                          << 0x0000000cU) 
                                                         | ((0x00000800U 
                                                             & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                << 4U)) 
                                                            | ((0x000007e0U 
                                                                & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                   >> 0x00000014U)) 
                                                               | (0x0000001eU 
                                                                  & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                     >> 7U)))))
                                                         : 
                                                        ((IData)(vlSelfRef.SoC__DOT__core__DOT__decode__DOT___GEN)
                                                          ? 
                                                         (0xfffff000U 
                                                          & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)
                                                          : 
                                                         (((- (IData)(
                                                                      (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                       >> 0x0000001fU))) 
                                                           << 0x00000014U) 
                                                          | ((0x6fU 
                                                              == 
                                                              (0x0000007fU 
                                                               & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr))
                                                              ? 
                                                             ((((0x000001feU 
                                                                 & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                    >> 0x0000000bU)) 
                                                                | (1U 
                                                                   & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                      >> 0x00000014U))) 
                                                               << 0x0000000bU) 
                                                              | (0x000007feU 
                                                                 & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                    >> 0x00000014U)))
                                                              : 
                                                             ((0x000ff000U 
                                                               & ((- (IData)(
                                                                             (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                              >> 0x0000001fU))) 
                                                                  << 0x0000000cU)) 
                                                              | (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                 >> 0x00000014U))))))))));
            __Vtemp_3[0U] = (IData)((((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_11)
                                       ? vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result
                                       : (((QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                           [
                                                           (((IData)(0x0000003fU) 
                                                             + 
                                                             (0x000007c0U 
                                                              & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                 >> 9U))) 
                                                            >> 5U)])) 
                                           << 0x00000020U) 
                                          | (QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                            [
                                                            (0x0000003eU 
                                                             & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                >> 0x0000000eU))])))) 
                                     & (- (QData)((IData)(
                                                          (0U 
                                                           != 
                                                           (0x0000001fU 
                                                            & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                               >> 0x0000000fU))))))));
            __Vtemp_3[1U] = (IData)(((((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_11)
                                        ? vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result
                                        : (((QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                            [
                                                            (((IData)(0x0000003fU) 
                                                              + 
                                                              (0x000007c0U 
                                                               & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                  >> 9U))) 
                                                             >> 5U)])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                             [
                                                             (0x0000003eU 
                                                              & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                 >> 0x0000000eU))])))) 
                                      & (- (QData)((IData)(
                                                           (0U 
                                                            != 
                                                            (0x0000001fU 
                                                             & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                >> 0x0000000fU))))))) 
                                     >> 0x00000020U));
            __Vtemp_3[2U] = (IData)(vlSelfRef.SoC__DOT__core__DOT___execute_io_out_result);
            __Vtemp_3[3U] = (IData)((vlSelfRef.SoC__DOT__core__DOT___execute_io_out_result 
                                     >> 0x00000020U));
            __Vtemp_3[4U] = (IData)(vlSelfRef.SoC__DOT__core__DOT___memory_io_out_result);
            __Vtemp_3[5U] = (IData)((vlSelfRef.SoC__DOT__core__DOT___memory_io_out_result 
                                     >> 0x00000020U));
            __Vtemp_3[6U] = (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result);
            __Vtemp_3[7U] = (IData)((vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result 
                                     >> 0x00000020U));
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val 
                = (((QData)((IData)(__Vtemp_3[(((IData)(0x0000003fU) 
                                                + (
                                                   ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_5) 
                                                    & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_14))
                                                    ? 0x40U
                                                    : 
                                                   (((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_7) 
                                                     & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3))
                                                     ? 0x80U
                                                     : 
                                                    (0x000000c0U 
                                                     & ((- (IData)((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_11))) 
                                                        << 6U))))) 
                                               >> 5U)])) 
                    << 0x00000020U) | (QData)((IData)(__Vtemp_3
                                                      [
                                                      ((((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_5) 
                                                         & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_14))
                                                         ? 0x40U
                                                         : 
                                                        (((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_7) 
                                                          & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3))
                                                          ? 0x80U
                                                          : 
                                                         (0x000000c0U 
                                                          & ((- (IData)((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_11))) 
                                                             << 6U)))) 
                                                       >> 5U)])));
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_memOp 
                = (7U & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                         >> 0x0000000cU));
            __Vtemp_6[0U] = (IData)((((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_10)
                                       ? vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result
                                       : (((QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                           [
                                                           (((IData)(0x0000003fU) 
                                                             + 
                                                             (0x000007c0U 
                                                              & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                 >> 0x0000000eU))) 
                                                            >> 5U)])) 
                                           << 0x00000020U) 
                                          | (QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                            [
                                                            (0x0000003eU 
                                                             & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                >> 0x00000013U))])))) 
                                     & (- (QData)((IData)(
                                                          (0U 
                                                           != 
                                                           (0x0000001fU 
                                                            & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                               >> 0x00000014U))))))));
            __Vtemp_6[1U] = (IData)(((((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_10)
                                        ? vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result
                                        : (((QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                            [
                                                            (((IData)(0x0000003fU) 
                                                              + 
                                                              (0x000007c0U 
                                                               & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                  >> 0x0000000eU))) 
                                                             >> 5U)])) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN
                                                             [
                                                             (0x0000003eU 
                                                              & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                 >> 0x00000013U))])))) 
                                      & (- (QData)((IData)(
                                                           (0U 
                                                            != 
                                                            (0x0000001fU 
                                                             & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                                >> 0x00000014U))))))) 
                                     >> 0x00000020U));
            __Vtemp_6[2U] = (IData)(vlSelfRef.SoC__DOT__core__DOT___execute_io_out_result);
            __Vtemp_6[3U] = (IData)((vlSelfRef.SoC__DOT__core__DOT___execute_io_out_result 
                                     >> 0x00000020U));
            __Vtemp_6[4U] = (IData)(vlSelfRef.SoC__DOT__core__DOT___memory_io_out_result);
            __Vtemp_6[5U] = (IData)((vlSelfRef.SoC__DOT__core__DOT___memory_io_out_result 
                                     >> 0x00000020U));
            __Vtemp_6[6U] = (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result);
            __Vtemp_6[7U] = (IData)((vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result 
                                     >> 0x00000020U));
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val 
                = (((QData)((IData)(__Vtemp_6[(((IData)(0x0000003fU) 
                                                + (
                                                   ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6) 
                                                    & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_14))
                                                    ? 0x40U
                                                    : 
                                                   (((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_8) 
                                                     & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3))
                                                     ? 0x80U
                                                     : 
                                                    (0x000000c0U 
                                                     & ((- (IData)((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_10))) 
                                                        << 6U))))) 
                                               >> 5U)])) 
                    << 0x00000020U) | (QData)((IData)(__Vtemp_6
                                                      [
                                                      ((((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6) 
                                                         & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_14))
                                                         ? 0x40U
                                                         : 
                                                        (((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_8) 
                                                          & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3))
                                                          ? 0x80U
                                                          : 
                                                         (0x000000c0U 
                                                          & ((- (IData)((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_10))) 
                                                             << 6U)))) 
                                                       >> 5U)])));
            vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd 
                = (0x0000001fU & ((vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                   >> 7U) & (- (IData)(
                                                       ((IData)(vlSelfRef.SoC__DOT__core__DOT__decode__DOT___GEN) 
                                                        | ((0x6fU 
                                                            == 
                                                            (0x0000007fU 
                                                             & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                           | ((0x67U 
                                                               == 
                                                               (0x0000007fU 
                                                                & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                              | ((3U 
                                                                  == 
                                                                  (0x0000007fU 
                                                                   & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                                 | (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))))))));
        }
        if (vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush) {
            vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_pc = 0ULL;
            vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr = 0U;
        } else if ((1U & (~ (IData)(vlSelfRef.SoC__DOT__core__DOT__pipe_stall)))) {
            vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_pc 
                = vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc;
            vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                = ((IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush)
                    ? 0x00000013U : ((0x0000000000001000ULL 
                                      > (vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
                                         - 0x0000000000001000ULL))
                                      ? (VSoC__ConstPool__CONST_h95b5ef3e_0
                                         [(7U & (IData)(
                                                        (vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
                                                         >> 2U)))] 
                                         & (- (IData)(
                                                      ((0x0000000000001000ULL 
                                                        > 
                                                        (vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
                                                         - 0x0000000000001000ULL)) 
                                                       & ((0U 
                                                           != 
                                                           (vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
                                                            >> 0x0000000cU)) 
                                                          & (0x0000000000002000ULL 
                                                             > vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc))))))
                                      : ((1U & (IData)(
                                                       (vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
                                                        >> 2U)))
                                          ? (IData)(
                                                    (vlSelfRef.SoC__DOT___sram_io_fetch_data 
                                                     >> 0x00000020U))
                                          : (IData)(vlSelfRef.SoC__DOT___sram_io_fetch_data))));
        }
        vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_result 
            = vlSelfRef.SoC__DOT__core__DOT___memory_io_out_result;
    }
    vlSelfRef.SoC__DOT__uart__DOT__baud_cnt = __Vdly__SoC__DOT__uart__DOT__baud_cnt;
    vlSelfRef.SoC__DOT__uart__DOT__bit_cnt = __Vdly__SoC__DOT__uart__DOT__bit_cnt;
    vlSelfRef.SoC__DOT__uart__DOT__shift_reg = __Vdly__SoC__DOT__uart__DOT__shift_reg;
    vlSelfRef.SoC__DOT__uart__DOT__tx_reg = __Vdly__SoC__DOT__uart__DOT__tx_reg;
    vlSelfRef.SoC__DOT__uart__DOT__state = __Vdly__SoC__DOT__uart__DOT__state;
    vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_valid 
        = __Vdly__SoC__DOT__core__DOT__if_id__DOT__reg_valid;
    if (__VdlySet__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0) {
        vlSelfRef.SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory[__VdlyDim0__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0] 
            = __VdlyVal__SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory__v0;
    }
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJal 
        = __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJal;
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr 
        = __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr;
    if (__VdlySet__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0) {
        vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory[__VdlyDim0__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0] 
            = __VdlyVal__SoC__DOT__sram__DOT__mem_ext__DOT__Memory__v0;
    }
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad 
        = __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_0 = __Vdly__SoC__DOT__dcache__DOT__valid_0;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_1 = __Vdly__SoC__DOT__dcache__DOT__valid_1;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_2 = __Vdly__SoC__DOT__dcache__DOT__valid_2;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_3 = __Vdly__SoC__DOT__dcache__DOT__valid_3;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_4 = __Vdly__SoC__DOT__dcache__DOT__valid_4;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_5 = __Vdly__SoC__DOT__dcache__DOT__valid_5;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_6 = __Vdly__SoC__DOT__dcache__DOT__valid_6;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_7 = __Vdly__SoC__DOT__dcache__DOT__valid_7;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_8 = __Vdly__SoC__DOT__dcache__DOT__valid_8;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_9 = __Vdly__SoC__DOT__dcache__DOT__valid_9;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_10 = __Vdly__SoC__DOT__dcache__DOT__valid_10;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_11 = __Vdly__SoC__DOT__dcache__DOT__valid_11;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_12 = __Vdly__SoC__DOT__dcache__DOT__valid_12;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_13 = __Vdly__SoC__DOT__dcache__DOT__valid_13;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_14 = __Vdly__SoC__DOT__dcache__DOT__valid_14;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_15 = __Vdly__SoC__DOT__dcache__DOT__valid_15;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_16 = __Vdly__SoC__DOT__dcache__DOT__valid_16;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_17 = __Vdly__SoC__DOT__dcache__DOT__valid_17;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_18 = __Vdly__SoC__DOT__dcache__DOT__valid_18;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_19 = __Vdly__SoC__DOT__dcache__DOT__valid_19;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_20 = __Vdly__SoC__DOT__dcache__DOT__valid_20;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_21 = __Vdly__SoC__DOT__dcache__DOT__valid_21;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_22 = __Vdly__SoC__DOT__dcache__DOT__valid_22;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_23 = __Vdly__SoC__DOT__dcache__DOT__valid_23;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_24 = __Vdly__SoC__DOT__dcache__DOT__valid_24;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_25 = __Vdly__SoC__DOT__dcache__DOT__valid_25;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_26 = __Vdly__SoC__DOT__dcache__DOT__valid_26;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_27 = __Vdly__SoC__DOT__dcache__DOT__valid_27;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_28 = __Vdly__SoC__DOT__dcache__DOT__valid_28;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_29 = __Vdly__SoC__DOT__dcache__DOT__valid_29;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_30 = __Vdly__SoC__DOT__dcache__DOT__valid_30;
    vlSelfRef.SoC__DOT__dcache__DOT__valid_31 = __Vdly__SoC__DOT__dcache__DOT__valid_31;
    vlSelfRef.io_uart_tx = vlSelfRef.SoC__DOT__uart__DOT__tx_reg;
    __VdfgRegularize_hebeb780c_0_2 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJal) 
                                      | (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[0U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_0);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[1U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_0 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[2U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_1);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[3U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_1 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[4U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_2);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[5U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_2 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[6U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_3);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[7U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_3 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[8U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_4);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[9U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_4 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[10U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_5);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[11U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_5 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[12U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_6);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[13U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_6 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[14U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_7);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[15U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_7 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[16U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_8);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[17U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_8 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[18U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_9);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[19U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_9 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[20U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_10);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[21U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_10 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[22U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_11);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[23U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_11 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[24U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_12);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[25U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_12 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[26U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_13);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[27U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_13 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[28U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_14);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[29U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_14 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[30U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_15);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[31U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_15 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[32U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_16);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[33U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_16 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[34U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_17);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[35U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_17 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[36U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_18);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[37U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_18 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[38U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_19);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[39U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_19 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[40U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_20);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[41U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_20 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[42U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_21);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[43U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_21 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[44U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_22);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[45U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_22 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[46U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_23);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[47U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_23 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[48U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_24);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[49U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_24 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[50U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_25);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[51U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_25 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[52U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_26);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[53U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_26 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[54U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_27);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[55U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_27 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[56U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_28);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[57U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_28 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[58U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_29);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[59U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_29 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[60U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_30);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[61U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_30 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[62U] 
        = (IData)(vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_31);
    vlSelfRef.SoC__DOT__core__DOT__regfile__DOT___GEN[63U] 
        = (IData)((vlSelfRef.SoC__DOT__core__DOT__regfile__DOT__regs_31 
                   >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isStore 
        = __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_isStore;
    vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid 
        = __Vdly__SoC__DOT__core__DOT__id_ex__DOT__reg_valid;
    vlSelfRef.SoC__DOT__core__DOT__execute__DOT___bu_io_target 
        = (vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc 
           + vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm);
    SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
        = (((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isAuipc)
             ? vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc
             : vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val) 
           & (- (QData)((IData)((1U & (~ (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLui)))))));
    SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
        = (((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_useImm) 
            | ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLui) 
               | (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isAuipc)))
            ? vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm
            : vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val);
    SoC__DOT__core__DOT__execute__DOT__bu__DOT___io_taken_T_7 
        = ((0U == (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_brOp)) 
           & (vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val 
              == vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val));
    vlSelfRef.SoC__DOT__core__DOT___writeback_io_wen 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_valid) 
           & (0U != (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)));
    vlSelfRef.SoC__DOT__core__DOT____Vcellinp__forward__io_ex_wen 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid) 
           | (IData)(__VdfgRegularize_hebeb780c_0_2));
    SoC__DOT___core_io_dcache_valid = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_valid) 
                                       & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad) 
                                          | (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore)));
    vlSelfRef.SoC__DOT___core_io_dcache_wdata = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val 
                                                 << 
                                                 (0x00000038U 
                                                  & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                                                     << 3U)));
    vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_data 
        = (0x000000ffU & VL_SHIFTL_III(8,8,6, (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val), 
                                       (0x00000038U 
                                        & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                                           << 3U))));
    __Vtemp_32[0U] = (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val);
    __Vtemp_32[1U] = (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val 
                              >> 0x00000020U));
    __Vtemp_32[2U] = 0U;
    __Vtemp_32[3U] = 0U;
    VL_SHIFTL_WWI(127,127,6, __Vtemp_33, __Vtemp_32, 
                  (0x00000038U & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                                  << 3U)));
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
        = __Vtemp_33[0U];
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
        = __Vtemp_33[1U];
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[2U] 
        = __Vtemp_33[2U];
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[3U] 
        = (0x7fffffffU & __Vtemp_33[3U]);
    SoC__DOT___core_io_dcache_wstrb = (0x000000ffU 
                                       & ((- (IData)((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore))) 
                                          & (((2U == (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp))
                                               ? ((IData)(0x0fU) 
                                                  << 
                                                  (7U 
                                                   & (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result)))
                                               : ((1U 
                                                   == (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp))
                                                   ? 
                                                  ((IData)(3U) 
                                                   << 
                                                   (7U 
                                                    & (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result)))
                                                   : 
                                                  ((- (IData)(
                                                              (0U 
                                                               == (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp)))) 
                                                   & ((IData)(1U) 
                                                      << 
                                                      (7U 
                                                       & (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result)))))) 
                                             | (- (IData)(
                                                          (3U 
                                                           == (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp)))))));
    SoC__DOT__sram_sel = ((0U != (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                  >> 0x0000001dU)) 
                          & (0x0000000020010000ULL 
                             > vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result));
    __Vtemp_43[0U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              + SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_43[1U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               + SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_43[2U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                              - SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2));
    __Vtemp_43[3U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                               - SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2) 
                              >> 0x00000020U));
    __Vtemp_43[4U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              & SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_43[5U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               & SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_43[6U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              | SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_43[7U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               | SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_43[8U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              ^ SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_43[9U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               ^ SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_43[10U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                               << (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_43[11U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                                << (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_43[12U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                               >> (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_43[13U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                                >> (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_43[14U] = (IData)(VL_SHIFTRS_QQI(64,64,6, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, 
                                             (0x0000003fU 
                                              & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_43[15U] = (IData)((VL_SHIFTRS_QQI(64,64,6, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, 
                                              (0x0000003fU 
                                               & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_43[16U] = (IData)((QData)((IData)(VL_LTS_IQQ(64, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_43[17U] = (IData)(((QData)((IData)(VL_LTS_IQQ(64, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_43[18U] = (SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                       < SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2);
    __Vtemp_43[19U] = 0U;
    __Vtemp_43[20U] = 0U;
    __Vtemp_43[21U] = 0U;
    __Vtemp_43[22U] = 0U;
    __Vtemp_43[23U] = 0U;
    __Vtemp_43[24U] = 0U;
    __Vtemp_43[25U] = 0U;
    __Vtemp_43[26U] = 0U;
    __Vtemp_43[27U] = 0U;
    __Vtemp_43[28U] = 0U;
    __Vtemp_43[29U] = 0U;
    __Vtemp_43[30U] = 0U;
    __Vtemp_43[31U] = 0U;
    vlSelfRef.SoC__DOT__core__DOT___execute_io_out_result 
        = ((IData)(__VdfgRegularize_hebeb780c_0_2) ? 
           (4ULL + vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc)
            : (((QData)((IData)(__Vtemp_43[(((IData)(0x0000003fU) 
                                             + ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                                << 6U)) 
                                            >> 5U)])) 
                << ((0U == (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                           << 6U)))
                     ? 0x00000020U : ((IData)(0x00000040U) 
                                      - (0x0000001fU 
                                         & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                            << 6U))))) 
               | (((0U == (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                          << 6U))) ? 0ULL
                    : ((QData)((IData)(__Vtemp_43[(
                                                   ((IData)(0x0000001fU) 
                                                    + 
                                                    ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                                     << 6U)) 
                                                   >> 5U)])) 
                       << ((IData)(0x00000020U) - (0x0000001fU 
                                                   & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                                      << 6U))))) 
                  | ((QData)((IData)(__Vtemp_43[(0x07fffffeU 
                                                 & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                                    << 1U))])) 
                     >> (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                        << 6U))))));
    SoC__DOT__uart_write = ((IData)(SoC__DOT___core_io_dcache_valid) 
                            & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore) 
                               & ((0U != (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                          >> 0x0000001cU)) 
                                  & (0x0000000010001000ULL 
                                     > vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result))));
    __Vtemp_58[23U] = ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                           >> 0x00000017U) | (0x000ffe00U 
                                              & ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                                          >> 0x00000020U)) 
                                                 << 9U))) 
                         | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
                             << 0x0000001eU) | (0xfff00000U 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                                            >> 0x00000020U)) 
                                                   << 9U)))) 
                        >> 0x00000018U) | ((((0x000fffffU 
                                              & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
                                                 >> 2U)) 
                                             | ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                                         >> 0x00000020U)) 
                                                >> 0x00000017U)) 
                                            | ((0x3ff00000U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
                                                   >> 2U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001eU))) 
                                           << 8U));
    __Vtemp_58[24U] = (((((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
                                          >> 2U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                    >> 0x00000020U)) 
                           >> 0x00000017U)) | ((0x3ff00000U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
                                                   >> 2U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001eU))) 
                        >> 0x00000018U) | ((((0x00080000U 
                                              & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                                 << 0x00000013U)) 
                                             | (0x000fffffU 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                                                            >> 0x00000020U)) 
                                                   >> 2U))) 
                                            | ((((0x000003ffU 
                                                  & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                                     >> 1U)) 
                                                 | ((IData)(
                                                            (vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                                                             >> 0x00000020U)) 
                                                    >> 0x00000016U)) 
                                                | ((0x7ffffc00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                                       >> 1U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001fU))) 
                                               << 0x00000014U)) 
                                           << 8U));
    __Vtemp_58[25U] = (((((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                          << 0x00000013U)) 
                          | (0x000fffffU & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                                                     >> 0x00000020U)) 
                                            >> 2U))) 
                         | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                                          >> 0x00000020U)) 
                                 >> 0x00000016U)) | 
                             ((0x7ffffc00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                          >> 0x00000020U)) 
                                 << 0x0000001fU))) 
                            << 0x00000014U)) >> 0x00000018U) 
                       | ((0x0fffff00U & ((((0x000003ffU 
                                             & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                                >> 1U)) 
                                            | ((IData)(
                                                       (vlSelfRef.SoC__DOT__dcache__DOT__tags_30 
                                                        >> 0x00000020U)) 
                                               >> 0x00000016U)) 
                                           | ((0x7ffffc00U 
                                               & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
                                                  >> 1U)) 
                                              | ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                          >> 0x00000020U)) 
                                                 << 0x0000001fU))) 
                                          >> 4U)) | 
                          (((0x000003ffU & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                     >> 0x00000020U)) 
                                            >> 1U)) 
                            | (0x7ffffc00U & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                       >> 0x00000020U)) 
                                              >> 1U))) 
                           << 0x0000001cU)));
    __Vtemp_58[26U] = ((0x000000ffU & (((0x000003ffU 
                                         & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                     >> 0x00000020U)) 
                                            >> 1U)) 
                                        | (0x7ffffc00U 
                                           & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                       >> 0x00000020U)) 
                                              >> 1U))) 
                                       >> 4U)) | (0x0fffff00U 
                                                  & (((0x000003ffU 
                                                       & ((IData)(
                                                                  (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                                   >> 0x00000020U)) 
                                                          >> 1U)) 
                                                      | (0x7ffffc00U 
                                                         & ((IData)(
                                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_31 
                                                                     >> 0x00000020U)) 
                                                            >> 1U))) 
                                                     >> 4U)));
    __Vtemp_73[23U] = ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
                           >> 0x00000017U) | (0x000ffe00U 
                                              & ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_13 
                                                          >> 0x00000020U)) 
                                                 << 9U))) 
                         | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_14) 
                             << 0x0000001eU) | (0xfff00000U 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_13 
                                                            >> 0x00000020U)) 
                                                   << 9U)))) 
                        >> 0x00000018U) | ((((0x000fffffU 
                                              & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_14) 
                                                 >> 2U)) 
                                             | ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_13 
                                                         >> 0x00000020U)) 
                                                >> 0x00000017U)) 
                                            | ((0x3ff00000U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_14) 
                                                   >> 2U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001eU))) 
                                           << 8U));
    __Vtemp_73[24U] = (((((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_14) 
                                          >> 2U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_13 
                                    >> 0x00000020U)) 
                           >> 0x00000017U)) | ((0x3ff00000U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_14) 
                                                   >> 2U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001eU))) 
                        >> 0x00000018U) | ((((0x00080000U 
                                              & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                                 << 0x00000013U)) 
                                             | (0x000fffffU 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                                                            >> 0x00000020U)) 
                                                   >> 2U))) 
                                            | ((((0x000003ffU 
                                                  & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                                     >> 1U)) 
                                                 | ((IData)(
                                                            (vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                                                             >> 0x00000020U)) 
                                                    >> 0x00000016U)) 
                                                | ((0x7ffffc00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                                       >> 1U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001fU))) 
                                               << 0x00000014U)) 
                                           << 8U));
    __Vtemp_73[25U] = (((((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                          << 0x00000013U)) 
                          | (0x000fffffU & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                                                     >> 0x00000020U)) 
                                            >> 2U))) 
                         | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                                          >> 0x00000020U)) 
                                 >> 0x00000016U)) | 
                             ((0x7ffffc00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                          >> 0x00000020U)) 
                                 << 0x0000001fU))) 
                            << 0x00000014U)) >> 0x00000018U) 
                       | ((0x0fffff00U & ((((0x000003ffU 
                                             & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                                >> 1U)) 
                                            | ((IData)(
                                                       (vlSelfRef.SoC__DOT__dcache__DOT__tags_14 
                                                        >> 0x00000020U)) 
                                               >> 0x00000016U)) 
                                           | ((0x7ffffc00U 
                                               & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
                                                  >> 1U)) 
                                              | ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                          >> 0x00000020U)) 
                                                 << 0x0000001fU))) 
                                          >> 4U)) | 
                          (((0x000003ffU & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                     >> 0x00000020U)) 
                                            >> 1U)) 
                            | (0x7ffffc00U & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                       >> 0x00000020U)) 
                                              >> 1U))) 
                           << 0x0000001cU)));
    __Vtemp_73[26U] = ((0x000000ffU & (((0x000003ffU 
                                         & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                     >> 0x00000020U)) 
                                            >> 1U)) 
                                        | (0x7ffffc00U 
                                           & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                       >> 0x00000020U)) 
                                              >> 1U))) 
                                       >> 4U)) | (0x0fffff00U 
                                                  & (((0x000003ffU 
                                                       & ((IData)(
                                                                  (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                                   >> 0x00000020U)) 
                                                          >> 1U)) 
                                                      | (0x7ffffc00U 
                                                         & ((IData)(
                                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_15 
                                                                     >> 0x00000020U)) 
                                                            >> 1U))) 
                                                     >> 4U)));
    __Vtemp_74[0U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_0);
    __Vtemp_74[1U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_1) 
                       << 0x00000015U) | (IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_0 
                                                  >> 0x00000020U)));
    __Vtemp_74[2U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_1) 
                       >> 0x0000000bU) | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_1 
                                                   >> 0x00000020U)) 
                                          << 0x00000015U));
    __Vtemp_74[3U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_2) 
                       << 0x0000000aU) | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_1 
                                                   >> 0x00000020U)) 
                                          >> 0x0000000bU));
    __Vtemp_74[4U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_2) 
                       >> 0x00000016U) | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_3) 
                                           << 0x0000001fU) 
                                          | ((IData)(
                                                     (vlSelfRef.SoC__DOT__dcache__DOT__tags_2 
                                                      >> 0x00000020U)) 
                                             << 0x0000000aU)));
    __Vtemp_74[5U] = (((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_3) 
                                       >> 1U)) | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_2 
                                                           >> 0x00000020U)) 
                                                  >> 0x00000016U)) 
                      | ((0x7ffffc00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_3) 
                                         >> 1U)) | 
                         ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_3 
                                   >> 0x00000020U)) 
                          << 0x0000001fU)));
    __Vtemp_74[6U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_4) 
                       << 0x00000014U) | ((0x000003ffU 
                                           & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_3 
                                                       >> 0x00000020U)) 
                                              >> 1U)) 
                                          | (0x7ffffc00U 
                                             & ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_3 
                                                         >> 0x00000020U)) 
                                                >> 1U))));
    __Vtemp_74[7U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_4) 
                       >> 0x0000000cU) | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_4 
                                                   >> 0x00000020U)) 
                                          << 0x00000014U));
    __Vtemp_74[8U] = (((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_5) 
                                       << 9U)) | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_4 
                                                           >> 0x00000020U)) 
                                                  >> 0x0000000cU)) 
                      | (0xfff00000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_5) 
                                        << 9U)));
    __Vtemp_74[9U] = ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_5) 
                        >> 0x00000017U) | (0x000ffe00U 
                                           & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_5 
                                                       >> 0x00000020U)) 
                                              << 9U))) 
                      | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_6) 
                          << 0x0000001eU) | (0xfff00000U 
                                             & ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_5 
                                                         >> 0x00000020U)) 
                                                << 9U))));
    __Vtemp_74[10U] = (((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_6) 
                                        >> 2U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_5 
                                                            >> 0x00000020U)) 
                                                   >> 0x00000017U)) 
                       | ((0x3ff00000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_6) 
                                          >> 2U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_6 
                                    >> 0x00000020U)) 
                           << 0x0000001eU)));
    __Vtemp_74[11U] = (((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_7) 
                                        << 0x00000013U)) 
                        | (0x000fffffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_6 
                                                   >> 0x00000020U)) 
                                          >> 2U))) 
                       | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_7) 
                                            >> 1U)) 
                            | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_6 
                                        >> 0x00000020U)) 
                               >> 0x00000016U)) | (
                                                   (0x7ffffc00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_7) 
                                                       >> 1U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001fU))) 
                          << 0x00000014U));
    __Vtemp_74[12U] = (((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_7) 
                                          >> 1U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_6 
                                    >> 0x00000020U)) 
                           >> 0x00000016U)) | ((0x7ffffc00U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_7) 
                                                   >> 1U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001fU))) 
                        >> 0x0000000cU) | (((0x000003ffU 
                                             & ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                         >> 0x00000020U)) 
                                                >> 1U)) 
                                            | (0x7ffffc00U 
                                               & ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                           >> 0x00000020U)) 
                                                  >> 1U))) 
                                           << 0x00000014U));
    __Vtemp_74[13U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_8) 
                        << 8U) | (((0x000003ffU & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                            >> 0x00000020U)) 
                                                   >> 1U)) 
                                   | (0x7ffffc00U & 
                                      ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                >> 0x00000020U)) 
                                       >> 1U))) >> 0x0000000cU));
    __Vtemp_74[14U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_8) 
                        >> 0x00000018U) | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_9) 
                                            << 0x0000001dU) 
                                           | ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_8 
                                                       >> 0x00000020U)) 
                                              << 8U)));
    __Vtemp_74[15U] = (((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_9) 
                                        >> 3U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_8 
                                                            >> 0x00000020U)) 
                                                   >> 0x00000018U)) 
                       | ((0x1fffff00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_9) 
                                          >> 3U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_9 
                                    >> 0x00000020U)) 
                           << 0x0000001dU)));
    __Vtemp_74[16U] = ((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_9 
                                                >> 0x00000020U)) 
                                       >> 3U)) | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_10) 
                                                   << 0x00000012U) 
                                                  | (0x1fffff00U 
                                                     & ((IData)(
                                                                (vlSelfRef.SoC__DOT__dcache__DOT__tags_9 
                                                                 >> 0x00000020U)) 
                                                        >> 3U))));
    __Vtemp_74[17U] = ((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_10) 
                                       >> 0x0000000eU)) 
                       | ((0x0003ff00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_10) 
                                          >> 0x0000000eU)) 
                          | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_10 
                                      >> 0x00000020U)) 
                             << 0x00000012U)));
    __Vtemp_74[18U] = (((0x00000080U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_11) 
                                        << 7U)) | (0x000000ffU 
                                                   & ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_10 
                                                               >> 0x00000020U)) 
                                                      >> 0x0000000eU))) 
                       | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_11) 
                                            >> 1U)) 
                            | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_10 
                                        >> 0x00000020U)) 
                               >> 0x00000016U)) | (
                                                   (0x7ffffc00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_11) 
                                                       >> 1U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_11 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001fU))) 
                          << 8U));
    __Vtemp_74[19U] = (((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_11) 
                                          >> 1U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_10 
                                    >> 0x00000020U)) 
                           >> 0x00000016U)) | ((0x7ffffc00U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_11) 
                                                   >> 1U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_11 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001fU))) 
                        >> 0x00000018U) | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_12) 
                                            << 0x0000001cU) 
                                           | (((0x000003ffU 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_11 
                                                            >> 0x00000020U)) 
                                                   >> 1U)) 
                                               | (0x7ffffc00U 
                                                  & ((IData)(
                                                             (vlSelfRef.SoC__DOT__dcache__DOT__tags_11 
                                                              >> 0x00000020U)) 
                                                     >> 1U))) 
                                              << 8U)));
    __Vtemp_74[20U] = (((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_12) 
                                        >> 4U)) | (
                                                   ((0x000003ffU 
                                                     & ((IData)(
                                                                (vlSelfRef.SoC__DOT__dcache__DOT__tags_11 
                                                                 >> 0x00000020U)) 
                                                        >> 1U)) 
                                                    | (0x7ffffc00U 
                                                       & ((IData)(
                                                                  (vlSelfRef.SoC__DOT__dcache__DOT__tags_11 
                                                                   >> 0x00000020U)) 
                                                          >> 1U))) 
                                                   >> 0x00000018U)) 
                       | ((0x0fffff00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_12) 
                                          >> 4U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_12 
                                    >> 0x00000020U)) 
                           << 0x0000001cU)));
    __Vtemp_74[21U] = ((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_12 
                                                >> 0x00000020U)) 
                                       >> 4U)) | ((
                                                   ((0x000ffe00U 
                                                     & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
                                                        << 9U)) 
                                                    | ((IData)(
                                                               (vlSelfRef.SoC__DOT__dcache__DOT__tags_12 
                                                                >> 0x00000020U)) 
                                                       >> 0x0000000cU)) 
                                                   | (0xfff00000U 
                                                      & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
                                                         << 9U))) 
                                                  << 8U));
    __Vtemp_74[22U] = (((((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
                                          << 9U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_12 
                                    >> 0x00000020U)) 
                           >> 0x0000000cU)) | (0xfff00000U 
                                               & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
                                                  << 9U))) 
                        >> 0x00000018U) | (((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
                                              >> 0x00000017U) 
                                             | (0x000ffe00U 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_13 
                                                            >> 0x00000020U)) 
                                                   << 9U))) 
                                            | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_14) 
                                                << 0x0000001eU) 
                                               | (0xfff00000U 
                                                  & ((IData)(
                                                             (vlSelfRef.SoC__DOT__dcache__DOT__tags_13 
                                                              >> 0x00000020U)) 
                                                     << 9U)))) 
                                           << 8U));
    __Vtemp_74[23U] = __Vtemp_73[23U];
    __Vtemp_74[24U] = __Vtemp_73[24U];
    __Vtemp_74[25U] = __Vtemp_73[25U];
    __Vtemp_74[26U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_16) 
                        << 0x00000010U) | __Vtemp_73[26U]);
    __Vtemp_74[27U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_16) 
                        >> 0x00000010U) | ((IData)(
                                                   (vlSelfRef.SoC__DOT__dcache__DOT__tags_16 
                                                    >> 0x00000020U)) 
                                           << 0x00000010U));
    __Vtemp_74[28U] = (((0x0000ffe0U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_17) 
                                        << 5U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_16 
                                                            >> 0x00000020U)) 
                                                   >> 0x00000010U)) 
                       | (0xffff0000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_17) 
                                         << 5U)));
    __Vtemp_74[29U] = ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_17) 
                         >> 0x0000001bU) | (0x0000ffe0U 
                                            & ((IData)(
                                                       (vlSelfRef.SoC__DOT__dcache__DOT__tags_17 
                                                        >> 0x00000020U)) 
                                               << 5U))) 
                       | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_18) 
                           << 0x0000001aU) | (0xffff0000U 
                                              & ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_17 
                                                          >> 0x00000020U)) 
                                                 << 5U))));
    __Vtemp_74[30U] = (((0x0000ffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_18) 
                                        >> 6U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_17 
                                                            >> 0x00000020U)) 
                                                   >> 0x0000001bU)) 
                       | ((0x03ff0000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_18) 
                                          >> 6U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_18 
                                    >> 0x00000020U)) 
                           << 0x0000001aU)));
    __Vtemp_74[31U] = (((0x00008000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_19) 
                                        << 0x0000000fU)) 
                        | (0x0000ffffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_18 
                                                   >> 0x00000020U)) 
                                          >> 6U))) 
                       | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_19) 
                                            >> 1U)) 
                            | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_18 
                                        >> 0x00000020U)) 
                               >> 0x00000016U)) | (
                                                   (0x7ffffc00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_19) 
                                                       >> 1U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_19 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001fU))) 
                          << 0x00000010U));
    __Vtemp_74[32U] = (((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_19) 
                                          >> 1U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_18 
                                    >> 0x00000020U)) 
                           >> 0x00000016U)) | ((0x7ffffc00U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_19) 
                                                   >> 1U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_19 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001fU))) 
                        >> 0x00000010U) | (((0x000003ffU 
                                             & ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_19 
                                                         >> 0x00000020U)) 
                                                >> 1U)) 
                                            | (0x7ffffc00U 
                                               & ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_19 
                                                           >> 0x00000020U)) 
                                                  >> 1U))) 
                                           << 0x00000010U));
    __Vtemp_74[33U] = (((0x0000fff0U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_20) 
                                        << 4U)) | (
                                                   ((0x000003ffU 
                                                     & ((IData)(
                                                                (vlSelfRef.SoC__DOT__dcache__DOT__tags_19 
                                                                 >> 0x00000020U)) 
                                                        >> 1U)) 
                                                    | (0x7ffffc00U 
                                                       & ((IData)(
                                                                  (vlSelfRef.SoC__DOT__dcache__DOT__tags_19 
                                                                   >> 0x00000020U)) 
                                                          >> 1U))) 
                                                   >> 0x00000010U)) 
                       | (0xffff0000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_20) 
                                         << 4U)));
    __Vtemp_74[34U] = ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_20) 
                         >> 0x0000001cU) | (0x0000fff0U 
                                            & ((IData)(
                                                       (vlSelfRef.SoC__DOT__dcache__DOT__tags_20 
                                                        >> 0x00000020U)) 
                                               << 4U))) 
                       | ((((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
                                            << 9U)) 
                            | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_20 
                                        >> 0x00000020U)) 
                               >> 0x0000000cU)) | (0xfff00000U 
                                                   & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
                                                      << 9U))) 
                          << 0x00000010U));
    __Vtemp_74[35U] = (((((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
                                          << 9U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_20 
                                    >> 0x00000020U)) 
                           >> 0x0000000cU)) | (0xfff00000U 
                                               & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
                                                  << 9U))) 
                        >> 0x00000010U) | (((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
                                              >> 0x00000017U) 
                                             | (0x000ffe00U 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_21 
                                                            >> 0x00000020U)) 
                                                   << 9U))) 
                                            | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_22) 
                                                << 0x0000001eU) 
                                               | (0xfff00000U 
                                                  & ((IData)(
                                                             (vlSelfRef.SoC__DOT__dcache__DOT__tags_21 
                                                              >> 0x00000020U)) 
                                                     << 9U)))) 
                                           << 0x00000010U));
    __Vtemp_74[36U] = ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
                           >> 0x00000017U) | (0x000ffe00U 
                                              & ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_21 
                                                          >> 0x00000020U)) 
                                                 << 9U))) 
                         | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_22) 
                             << 0x0000001eU) | (0xfff00000U 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_21 
                                                            >> 0x00000020U)) 
                                                   << 9U)))) 
                        >> 0x00000010U) | ((((0x000fffffU 
                                              & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_22) 
                                                 >> 2U)) 
                                             | ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_21 
                                                         >> 0x00000020U)) 
                                                >> 0x00000017U)) 
                                            | ((0x3ff00000U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_22) 
                                                   >> 2U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001eU))) 
                                           << 0x00000010U));
    __Vtemp_74[37U] = (((((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_22) 
                                          >> 2U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_21 
                                    >> 0x00000020U)) 
                           >> 0x00000017U)) | ((0x3ff00000U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_22) 
                                                   >> 2U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001eU))) 
                        >> 0x00000010U) | ((((0x00080000U 
                                              & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                                 << 0x00000013U)) 
                                             | (0x000fffffU 
                                                & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                                            >> 0x00000020U)) 
                                                   >> 2U))) 
                                            | ((((0x000003ffU 
                                                  & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                                     >> 1U)) 
                                                 | ((IData)(
                                                            (vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                                             >> 0x00000020U)) 
                                                    >> 0x00000016U)) 
                                                | ((0x7ffffc00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                                       >> 1U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001fU))) 
                                               << 0x00000014U)) 
                                           << 0x00000010U));
    __Vtemp_74[38U] = (((((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                          << 0x00000013U)) 
                          | (0x000fffffU & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                                     >> 0x00000020U)) 
                                            >> 2U))) 
                         | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                          >> 0x00000020U)) 
                                 >> 0x00000016U)) | 
                             ((0x7ffffc00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                          >> 0x00000020U)) 
                                 << 0x0000001fU))) 
                            << 0x00000014U)) >> 0x00000010U) 
                       | (0xffff0000U & ((((0x000003ffU 
                                            & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                               >> 1U)) 
                                           | ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                                       >> 0x00000020U)) 
                                              >> 0x00000016U)) 
                                          | ((0x7ffffc00U 
                                              & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                                 >> 1U)) 
                                             | ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                         >> 0x00000020U)) 
                                                << 0x0000001fU))) 
                                         << 4U)));
    __Vtemp_74[39U] = ((((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                           >> 1U)) 
                           | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_22 
                                       >> 0x00000020U)) 
                              >> 0x00000016U)) | ((0x7ffffc00U 
                                                   & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
                                                      >> 1U)) 
                                                  | ((IData)(
                                                             (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                              >> 0x00000020U)) 
                                                     << 0x0000001fU))) 
                         >> 0x0000001cU) | (0x0000fff0U 
                                            & (((0x000003ffU 
                                                 & ((IData)(
                                                            (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                             >> 0x00000020U)) 
                                                    >> 1U)) 
                                                | (0x7ffffc00U 
                                                   & ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                               >> 0x00000020U)) 
                                                      >> 1U))) 
                                               << 4U))) 
                       | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_24) 
                           << 0x00000018U) | (0xffff0000U 
                                              & (((0x000003ffU 
                                                   & ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                               >> 0x00000020U)) 
                                                      >> 1U)) 
                                                  | (0x7ffffc00U 
                                                     & ((IData)(
                                                                (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                                 >> 0x00000020U)) 
                                                        >> 1U))) 
                                                 << 4U))));
    __Vtemp_74[40U] = (((0x0000ffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_24) 
                                        >> 8U)) | (
                                                   ((0x000003ffU 
                                                     & ((IData)(
                                                                (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                                 >> 0x00000020U)) 
                                                        >> 1U)) 
                                                    | (0x7ffffc00U 
                                                       & ((IData)(
                                                                  (vlSelfRef.SoC__DOT__dcache__DOT__tags_23 
                                                                   >> 0x00000020U)) 
                                                          >> 1U))) 
                                                   >> 0x0000001cU)) 
                       | ((0x00ff0000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_24) 
                                          >> 8U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_24 
                                    >> 0x00000020U)) 
                           << 0x00000018U)));
    __Vtemp_74[41U] = (((0x0000e000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_25) 
                                        << 0x0000000dU)) 
                        | (0x0000ffffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_24 
                                                   >> 0x00000020U)) 
                                          >> 8U))) 
                       | ((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_25) 
                                            >> 3U)) 
                            | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_24 
                                        >> 0x00000020U)) 
                               >> 0x00000018U)) | (
                                                   (0x1fffff00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_25) 
                                                       >> 3U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001dU))) 
                          << 0x00000010U));
    __Vtemp_74[42U] = (((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_25) 
                                          >> 3U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_24 
                                    >> 0x00000020U)) 
                           >> 0x00000018U)) | ((0x1fffff00U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_25) 
                                                   >> 3U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001dU))) 
                        >> 0x00000010U) | (((0x000000ffU 
                                             & ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
                                                         >> 0x00000020U)) 
                                                >> 3U)) 
                                            | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_26) 
                                                << 0x00000012U) 
                                               | (0x1fffff00U 
                                                  & ((IData)(
                                                             (vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
                                                              >> 0x00000020U)) 
                                                     >> 3U)))) 
                                           << 0x00000010U));
    __Vtemp_74[43U] = ((((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
                                                  >> 0x00000020U)) 
                                         >> 3U)) | 
                         (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_26) 
                           << 0x00000012U) | (0x1fffff00U 
                                              & ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
                                                          >> 0x00000020U)) 
                                                 >> 3U)))) 
                        >> 0x00000010U) | (((0x000000ffU 
                                             & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_26) 
                                                >> 0x0000000eU)) 
                                            | ((0x0003ff00U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_26) 
                                                   >> 0x0000000eU)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                                                           >> 0x00000020U)) 
                                                  << 0x00000012U))) 
                                           << 0x00000010U));
    __Vtemp_74[44U] = ((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_26) 
                                         >> 0x0000000eU)) 
                         | ((0x0003ff00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_26) 
                                            >> 0x0000000eU)) 
                            | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                                        >> 0x00000020U)) 
                               << 0x00000012U))) >> 0x00000010U) 
                       | ((((0x00000080U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                            << 7U)) 
                            | (0x000000ffU & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                                                       >> 0x00000020U)) 
                                              >> 0x0000000eU))) 
                           | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                                >> 1U)) 
                                | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                                            >> 0x00000020U)) 
                                   >> 0x00000016U)) 
                               | ((0x7ffffc00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                                  >> 1U)) 
                                  | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                              >> 0x00000020U)) 
                                     << 0x0000001fU))) 
                              << 8U)) << 0x00000010U));
    __Vtemp_74[45U] = (((((0x00000080U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                          << 7U)) | 
                          (0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                                                   >> 0x00000020U)) 
                                          >> 0x0000000eU))) 
                         | ((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                                          >> 0x00000020U)) 
                                 >> 0x00000016U)) | 
                             ((0x7ffffc00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                              >> 1U)) 
                              | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                          >> 0x00000020U)) 
                                 << 0x0000001fU))) 
                            << 8U)) >> 0x00000010U) 
                       | ((0x00ff0000U & ((((0x000003ffU 
                                             & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                                >> 1U)) 
                                            | ((IData)(
                                                       (vlSelfRef.SoC__DOT__dcache__DOT__tags_26 
                                                        >> 0x00000020U)) 
                                               >> 0x00000016U)) 
                                           | ((0x7ffffc00U 
                                               & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
                                                  >> 1U)) 
                                              | ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                          >> 0x00000020U)) 
                                                 << 0x0000001fU))) 
                                          >> 8U)) | 
                          (((0x000003ffU & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                     >> 0x00000020U)) 
                                            >> 1U)) 
                            | (0x7ffffc00U & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                       >> 0x00000020U)) 
                                              >> 1U))) 
                           << 0x00000018U)));
    __Vtemp_74[46U] = (((0x0000f000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_28) 
                                        << 0x0000000cU)) 
                        | (0x0000ffffU & (((0x000003ffU 
                                            & ((IData)(
                                                       (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                        >> 0x00000020U)) 
                                               >> 1U)) 
                                           | (0x7ffffc00U 
                                              & ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                          >> 0x00000020U)) 
                                                 >> 1U))) 
                                          >> 8U))) 
                       | ((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_28) 
                                            >> 4U)) 
                            | (((0x000003ffU & ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                         >> 0x00000020U)) 
                                                >> 1U)) 
                                | (0x7ffffc00U & ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                           >> 0x00000020U)) 
                                                  >> 1U))) 
                               >> 0x00000018U)) | (
                                                   (0x0fffff00U 
                                                    & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_28) 
                                                       >> 4U)) 
                                                   | ((IData)(
                                                              (vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                                                               >> 0x00000020U)) 
                                                      << 0x0000001cU))) 
                          << 0x00000010U));
    __Vtemp_74[47U] = (((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_28) 
                                          >> 4U)) | 
                          (((0x000003ffU & ((IData)(
                                                    (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                     >> 0x00000020U)) 
                                            >> 1U)) 
                            | (0x7ffffc00U & ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_27 
                                                       >> 0x00000020U)) 
                                              >> 1U))) 
                           >> 0x00000018U)) | ((0x0fffff00U 
                                                & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_28) 
                                                   >> 4U)) 
                                               | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                                                           >> 0x00000020U)) 
                                                  << 0x0000001cU))) 
                        >> 0x00000010U) | (((0x000000ffU 
                                             & ((IData)(
                                                        (vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                                                         >> 0x00000020U)) 
                                                >> 4U)) 
                                            | ((((0x000ffe00U 
                                                  & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                                     << 9U)) 
                                                 | ((IData)(
                                                            (vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                                                             >> 0x00000020U)) 
                                                    >> 0x0000000cU)) 
                                                | (0xfff00000U 
                                                   & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                                      << 9U))) 
                                               << 8U)) 
                                           << 0x00000010U));
    __Vtemp_74[48U] = ((((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                                                  >> 0x00000020U)) 
                                         >> 4U)) | 
                         ((((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                            << 9U)) 
                            | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                                        >> 0x00000020U)) 
                               >> 0x0000000cU)) | (0xfff00000U 
                                                   & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                                      << 9U))) 
                          << 8U)) >> 0x00000010U) | 
                       ((0x00ff0000U & ((((0x000ffe00U 
                                           & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                              << 9U)) 
                                          | ((IData)(
                                                     (vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
                                                      >> 0x00000020U)) 
                                             >> 0x0000000cU)) 
                                         | (0xfff00000U 
                                            & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                               << 9U))) 
                                        >> 8U)) | (
                                                   ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                                      >> 0x00000017U) 
                                                     | (0x000ffe00U 
                                                        & ((IData)(
                                                                   (vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                                                    >> 0x00000020U)) 
                                                           << 9U))) 
                                                    | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
                                                        << 0x0000001eU) 
                                                       | (0xfff00000U 
                                                          & ((IData)(
                                                                     (vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                                                      >> 0x00000020U)) 
                                                             << 9U)))) 
                                                   << 0x00000018U)));
    __Vtemp_74[49U] = ((0x0000ffffU & (((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
                                          >> 0x00000017U) 
                                         | (0x000ffe00U 
                                            & ((IData)(
                                                       (vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                                        >> 0x00000020U)) 
                                               << 9U))) 
                                        | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
                                            << 0x0000001eU) 
                                           | (0xfff00000U 
                                              & ((IData)(
                                                         (vlSelfRef.SoC__DOT__dcache__DOT__tags_29 
                                                          >> 0x00000020U)) 
                                                 << 9U)))) 
                                       >> 8U)) | (__Vtemp_58[23U] 
                                                  << 0x00000010U));
    __Vtemp_74[50U] = ((__Vtemp_58[23U] >> 0x00000010U) 
                       | (__Vtemp_58[24U] << 0x00000010U));
    __Vtemp_74[51U] = ((__Vtemp_58[24U] >> 0x00000010U) 
                       | (__Vtemp_58[25U] << 0x00000010U));
    __Vtemp_74[52U] = ((__Vtemp_58[25U] >> 0x00000010U) 
                       | (__Vtemp_58[26U] << 0x00000010U));
    vlSelfRef.SoC__DOT__dcache__DOT__hit = ((IData)(SoC__DOT___core_io_dcache_valid) 
                                            & (((((((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_31) 
                                                        << 3U) 
                                                       | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_30) 
                                                          << 2U)) 
                                                      | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_29) 
                                                          << 1U) 
                                                         | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_28))) 
                                                     << 0x0000000cU) 
                                                    | (((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_27) 
                                                          << 3U) 
                                                         | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_26) 
                                                            << 2U)) 
                                                        | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_25) 
                                                            << 1U) 
                                                           | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_24))) 
                                                       << 8U)) 
                                                   | ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_23) 
                                                          << 3U) 
                                                         | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_22) 
                                                            << 2U)) 
                                                        | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_21) 
                                                            << 1U) 
                                                           | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_20))) 
                                                       << 4U) 
                                                      | ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_19) 
                                                           << 3U) 
                                                          | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_18) 
                                                             << 2U)) 
                                                         | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_17) 
                                                             << 1U) 
                                                            | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_16))))) 
                                                  << 0x00000010U) 
                                                 | (((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_15) 
                                                         << 3U) 
                                                        | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_14) 
                                                           << 2U)) 
                                                       | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_13) 
                                                           << 1U) 
                                                          | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_12))) 
                                                      << 0x0000000cU) 
                                                     | (((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_11) 
                                                           << 3U) 
                                                          | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_10) 
                                                             << 2U)) 
                                                         | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_9) 
                                                             << 1U) 
                                                            | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_8))) 
                                                        << 8U)) 
                                                    | ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_7) 
                                                           << 3U) 
                                                          | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_6) 
                                                             << 2U)) 
                                                         | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_5) 
                                                             << 1U) 
                                                            | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_4))) 
                                                        << 4U) 
                                                       | ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_3) 
                                                            << 3U) 
                                                           | ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_2) 
                                                              << 2U)) 
                                                          | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_1) 
                                                              << 1U) 
                                                             | (IData)(vlSelfRef.SoC__DOT__dcache__DOT__valid_0)))))) 
                                                >> 
                                                (0x0000001fU 
                                                 & (IData)(
                                                           (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                            >> 6U)))) 
                                               & ((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                   >> 0x0000000bU) 
                                                  == 
                                                  (0x001fffffffffffffULL 
                                                   & ((((QData)((IData)(__Vtemp_74
                                                                        [
                                                                        (((IData)(0x00000034U) 
                                                                          + 
                                                                          (0x000007ffU 
                                                                           & ((IData)(0x00000035U) 
                                                                              * 
                                                                              (0x0000001fU 
                                                                               & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 6U)))))) 
                                                                         >> 5U)])) 
                                                        << 
                                                        ((0U 
                                                          == 
                                                          (0x0000001fU 
                                                           & ((IData)(0x00000035U) 
                                                              * 
                                                              (0x0000001fU 
                                                               & (IData)(
                                                                         (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                          >> 6U))))))
                                                          ? 0x00000020U
                                                          : 
                                                         ((IData)(0x00000040U) 
                                                          - 
                                                          (0x0000001fU 
                                                           & ((IData)(0x00000035U) 
                                                              * 
                                                              (0x0000001fU 
                                                               & (IData)(
                                                                         (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                          >> 6U)))))))) 
                                                       | (((0U 
                                                            == 
                                                            (0x0000001fU 
                                                             & ((IData)(0x00000035U) 
                                                                * 
                                                                (0x0000001fU 
                                                                 & (IData)(
                                                                           (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                            >> 6U))))))
                                                            ? 0ULL
                                                            : 
                                                           ((QData)((IData)(__Vtemp_74
                                                                            [
                                                                            (((IData)(0x0000001fU) 
                                                                              + 
                                                                              (0x000007ffU 
                                                                               & ((IData)(0x00000035U) 
                                                                                * 
                                                                                (0x0000001fU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 6U)))))) 
                                                                             >> 5U)])) 
                                                            << 
                                                            ((IData)(0x00000020U) 
                                                             - 
                                                             (0x0000001fU 
                                                              & ((IData)(0x00000035U) 
                                                                 * 
                                                                 (0x0000001fU 
                                                                  & (IData)(
                                                                            (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                             >> 6U)))))))) 
                                                          | ((QData)((IData)(__Vtemp_74
                                                                             [
                                                                             (0x0000003fU 
                                                                              & (((IData)(0x00000035U) 
                                                                                * 
                                                                                (0x0000001fU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 6U)))) 
                                                                                >> 5U))])) 
                                                             >> 
                                                             (0x0000001fU 
                                                              & ((IData)(0x00000035U) 
                                                                 * 
                                                                 (0x0000001fU 
                                                                  & (IData)(
                                                                            (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                             >> 6U)))))))) 
                                                      & (- (QData)((IData)(
                                                                           (0x069fU 
                                                                            >= 
                                                                            (0x000007ffU 
                                                                             & ((IData)(0x00000035U) 
                                                                                * 
                                                                                (0x0000001fU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 6U))))))))))))));
    vlSelfRef.SoC__DOT__sram__DOT__mergedWord = (((QData)((IData)(
                                                                  ((((0x0000ff00U 
                                                                      & (((0x00000080U 
                                                                           & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                           ? 
                                                                          ((SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
                                                                            << 8U) 
                                                                           | (SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
                                                                              >> 0x00000018U))
                                                                           : (IData)(
                                                                                (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))] 
                                                                                >> 0x00000038U))) 
                                                                         << 8U)) 
                                                                     | (0x000000ffU 
                                                                        & ((0x00000040U 
                                                                            & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                            ? 
                                                                           ((SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
                                                                             << 0x00000010U) 
                                                                            | (SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
                                                                               >> 0x00000010U))
                                                                            : (IData)(
                                                                                (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))] 
                                                                                >> 0x00000030U))))) 
                                                                    << 0x00000010U) 
                                                                   | ((0x0000ff00U 
                                                                       & (((0x00000020U 
                                                                            & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                            ? 
                                                                           ((SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
                                                                             << 0x00000018U) 
                                                                            | (SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
                                                                               >> 8U))
                                                                            : (IData)(
                                                                                (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))] 
                                                                                >> 0x00000028U))) 
                                                                          << 8U)) 
                                                                      | (0x000000ffU 
                                                                         & ((0x00000010U 
                                                                             & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                             ? SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U]
                                                                             : (IData)(
                                                                                (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))] 
                                                                                >> 0x00000020U)))))))) 
                                                  << 0x00000020U) 
                                                 | (QData)((IData)(
                                                                   ((((0x0000ff00U 
                                                                       & (((8U 
                                                                            & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                            ? 
                                                                           ((SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
                                                                             << 8U) 
                                                                            | (SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
                                                                               >> 0x00000018U))
                                                                            : (IData)(
                                                                                (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))] 
                                                                                >> 0x00000018U))) 
                                                                          << 8U)) 
                                                                      | (0x000000ffU 
                                                                         & ((4U 
                                                                             & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                             ? 
                                                                            ((SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
                                                                              << 0x00000010U) 
                                                                             | (SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
                                                                                >> 0x00000010U))
                                                                             : (IData)(
                                                                                (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))] 
                                                                                >> 0x00000010U))))) 
                                                                     << 0x00000010U) 
                                                                    | ((0x0000ff00U 
                                                                        & (((2U 
                                                                             & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                             ? 
                                                                            ((SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
                                                                              << 0x00000018U) 
                                                                             | (SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
                                                                                >> 8U))
                                                                             : (IData)(
                                                                                (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))] 
                                                                                >> 8U))) 
                                                                           << 8U)) 
                                                                       | (0x000000ffU 
                                                                          & ((1U 
                                                                              & (IData)(SoC__DOT___core_io_dcache_wstrb))
                                                                              ? (IData)(vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_data)
                                                                              : (IData)(vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                                                                [
                                                                                (0x00001fffU 
                                                                                & (IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 3U)))]))))))));
    SoC__DOT____Vcellinp__sram__io_wen = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore) 
                                          & (IData)(SoC__DOT__sram_sel));
    SoC__DOT__sram_io_valid = ((IData)(SoC__DOT___core_io_dcache_valid) 
                               & (IData)(SoC__DOT__sram_sel));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_3 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_valid) 
                                                & (0U 
                                                   != (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rd)));
    vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_valid 
        = ((0U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
           & (IData)(SoC__DOT__uart_write));
    vlSelfRef.SoC__DOT__sram__DOT___GEN = ((IData)(SoC__DOT__sram_io_valid) 
                                           & (IData)(SoC__DOT____Vcellinp__sram__io_wen));
    vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid 
        = ((~ (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore)) 
           & (IData)(SoC__DOT__sram_io_valid));
    vlSelfRef.SoC__DOT___sram_io_rdata = (vlSelfRef.SoC__DOT__sram__DOT__mem_ext__DOT__Memory
                                          [(0x00001fffU 
                                            & (IData)(
                                                      (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                       >> 3U)))] 
                                          & (- (QData)((IData)(
                                                               ((~ (IData)(SoC__DOT____Vcellinp__sram__io_wen)) 
                                                                & (IData)(SoC__DOT__sram_io_valid))))));
    vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall 
        = ((0U != (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
           & (IData)(SoC__DOT__uart_write));
    __Vtemp_105[0U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_0);
    __Vtemp_105[1U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_0 
                               >> 0x00000020U));
    __Vtemp_105[2U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_1);
    __Vtemp_105[3U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_1 
                               >> 0x00000020U));
    __Vtemp_105[4U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_2);
    __Vtemp_105[5U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_2 
                               >> 0x00000020U));
    __Vtemp_105[6U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_3);
    __Vtemp_105[7U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_3 
                               >> 0x00000020U));
    __Vtemp_105[8U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_4);
    __Vtemp_105[9U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_4 
                               >> 0x00000020U));
    __Vtemp_105[10U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_5);
    __Vtemp_105[11U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_5 
                                >> 0x00000020U));
    __Vtemp_105[12U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_6);
    __Vtemp_105[13U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_6 
                                >> 0x00000020U));
    __Vtemp_105[14U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_7);
    __Vtemp_105[15U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_7 
                                >> 0x00000020U));
    __Vtemp_105[16U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_8);
    __Vtemp_105[17U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_8 
                                >> 0x00000020U));
    __Vtemp_105[18U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_9);
    __Vtemp_105[19U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_9 
                                >> 0x00000020U));
    __Vtemp_105[20U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_10);
    __Vtemp_105[21U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_10 
                                >> 0x00000020U));
    __Vtemp_105[22U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_11);
    __Vtemp_105[23U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_11 
                                >> 0x00000020U));
    __Vtemp_105[24U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_12);
    __Vtemp_105[25U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_12 
                                >> 0x00000020U));
    __Vtemp_105[26U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_13);
    __Vtemp_105[27U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_13 
                                >> 0x00000020U));
    __Vtemp_105[28U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_14);
    __Vtemp_105[29U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_14 
                                >> 0x00000020U));
    __Vtemp_105[30U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_15);
    __Vtemp_105[31U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_15 
                                >> 0x00000020U));
    __Vtemp_105[32U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_16);
    __Vtemp_105[33U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_16 
                                >> 0x00000020U));
    __Vtemp_105[34U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_17);
    __Vtemp_105[35U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_17 
                                >> 0x00000020U));
    __Vtemp_105[36U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_18);
    __Vtemp_105[37U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_18 
                                >> 0x00000020U));
    __Vtemp_105[38U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_19);
    __Vtemp_105[39U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_19 
                                >> 0x00000020U));
    __Vtemp_105[40U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_20);
    __Vtemp_105[41U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_20 
                                >> 0x00000020U));
    __Vtemp_105[42U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_21);
    __Vtemp_105[43U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_21 
                                >> 0x00000020U));
    __Vtemp_105[44U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_22);
    __Vtemp_105[45U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_22 
                                >> 0x00000020U));
    __Vtemp_105[46U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_23);
    __Vtemp_105[47U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_23 
                                >> 0x00000020U));
    __Vtemp_105[48U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_24);
    __Vtemp_105[49U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_24 
                                >> 0x00000020U));
    __Vtemp_105[50U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_25);
    __Vtemp_105[51U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_25 
                                >> 0x00000020U));
    __Vtemp_105[52U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_26);
    __Vtemp_105[53U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_26 
                                >> 0x00000020U));
    __Vtemp_105[54U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_27);
    __Vtemp_105[55U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_27 
                                >> 0x00000020U));
    __Vtemp_105[56U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_28);
    __Vtemp_105[57U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_28 
                                >> 0x00000020U));
    __Vtemp_105[58U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_29);
    __Vtemp_105[59U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_29 
                                >> 0x00000020U));
    __Vtemp_105[60U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_30);
    __Vtemp_105[61U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_30 
                                >> 0x00000020U));
    __Vtemp_105[62U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_31);
    __Vtemp_105[63U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_31 
                                >> 0x00000020U));
    SoC__DOT____Vcellinp__core__io_dcache_rdata = ((IData)(SoC__DOT__sram_sel)
                                                    ? vlSelfRef.SoC__DOT___sram_io_rdata
                                                    : 
                                                   ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid)
                                                     ? vlSelfRef.SoC__DOT___sram_io_rdata
                                                     : 
                                                    ((((QData)((IData)(__Vtemp_105
                                                                       [
                                                                       (((IData)(0x0000003fU) 
                                                                         + 
                                                                         (0x000007c0U 
                                                                          & ((IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 6U)) 
                                                                             << 6U))) 
                                                                        >> 5U)])) 
                                                       << 0x00000020U) 
                                                      | (QData)((IData)(__Vtemp_105
                                                                        [
                                                                        (0x0000003eU 
                                                                         & ((IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 6U)) 
                                                                            << 1U))]))) 
                                                     & (- (QData)((IData)(
                                                                          ((~ (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore)) 
                                                                           & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__hit))))))));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_14 = ((0U 
                                                  != (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd)) 
                                                 & (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__forward__io_ex_wen));
    __VdfgRegularize_hebeb780c_0_12 = ((0U != (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd)) 
                                       & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad) 
                                          & (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid)));
    SoC__DOT__core__DOT__memory__DOT__shiftedLoad = 
        (SoC__DOT____Vcellinp__core__io_dcache_rdata 
         >> (0x00000038U & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                            << 3U)));
    vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
        = __Vdly__SoC__DOT__core__DOT__frontend__DOT__pc;
    vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush 
        = (((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isBranch) 
            & (((((((vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val 
                     >= vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val) 
                    << 3U) | ((vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val 
                               < vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val) 
                              << 2U)) | ((VL_GTES_IQQ(64, vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val, vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val) 
                                          << 1U) | 
                                         VL_LTS_IQQ(64, vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val, vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val))) 
                 << 4U) | ((0x0000000cU & ((- (IData)((IData)(SoC__DOT__core__DOT__execute__DOT__bu__DOT___io_taken_T_7))) 
                                           << 2U)) 
                           | (((vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val 
                                != vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val) 
                               << 1U) | (IData)(SoC__DOT__core__DOT__execute__DOT__bu__DOT___io_taken_T_7)))) 
               >> (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_brOp))) 
           | (IData)(__VdfgRegularize_hebeb780c_0_2));
    __Vtemp_113[0U] = (IData)((((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                               >> 7U)))))) 
                                << 8U) | (QData)((IData)(
                                                         (0x000000ffU 
                                                          & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))));
    __Vtemp_113[1U] = (IData)(((((- (QData)((IData)(
                                                    (1U 
                                                     & (IData)(
                                                               (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                                >> 7U)))))) 
                                 << 8U) | (QData)((IData)(
                                                          (0x000000ffU 
                                                           & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))) 
                               >> 0x00000020U));
    __Vtemp_113[2U] = (IData)((((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                               >> 0x0000000fU)))))) 
                                << 0x00000010U) | (QData)((IData)(
                                                                  (0x0000ffffU 
                                                                   & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))));
    __Vtemp_113[3U] = (IData)(((((- (QData)((IData)(
                                                    (1U 
                                                     & (IData)(
                                                               (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                                >> 0x0000000fU)))))) 
                                 << 0x00000010U) | (QData)((IData)(
                                                                   (0x0000ffffU 
                                                                    & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))) 
                               >> 0x00000020U));
    __Vtemp_113[4U] = (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad);
    __Vtemp_113[5U] = (- (IData)((1U & (IData)((SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                >> 0x0000001fU)))));
    __Vtemp_113[6U] = (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad);
    __Vtemp_113[7U] = (IData)((SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                               >> 0x00000020U));
    __Vtemp_113[8U] = (IData)((QData)((IData)((0x000000ffU 
                                               & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))));
    __Vtemp_113[9U] = (IData)(((QData)((IData)((0x000000ffU 
                                                & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))) 
                               >> 0x00000020U));
    __Vtemp_113[10U] = (IData)((QData)((IData)((0x0000ffffU 
                                                & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))));
    __Vtemp_113[11U] = (IData)(((QData)((IData)((0x0000ffffU 
                                                 & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))) 
                                >> 0x00000020U));
    __Vtemp_113[12U] = (IData)((QData)((IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)));
    __Vtemp_113[13U] = (IData)(((QData)((IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)) 
                                >> 0x00000020U));
    __Vtemp_113[14U] = (IData)(SoC__DOT____Vcellinp__core__io_dcache_rdata);
    __Vtemp_113[15U] = (IData)((SoC__DOT____Vcellinp__core__io_dcache_rdata 
                                >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT___memory_io_out_result 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad)
            ? (((QData)((IData)(__Vtemp_113[(((IData)(0x0000003fU) 
                                              + ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                                 << 6U)) 
                                             >> 5U)])) 
                << ((0U == (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                           << 6U)))
                     ? 0x00000020U : ((IData)(0x00000040U) 
                                      - (0x0000001fU 
                                         & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                            << 6U))))) 
               | (((0U == (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                          << 6U))) ? 0ULL
                    : ((QData)((IData)(__Vtemp_113[
                                       (((IData)(0x0000001fU) 
                                         + ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                            << 6U)) 
                                        >> 5U)])) << 
                       ((IData)(0x00000020U) - (0x0000001fU 
                                                & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                                   << 6U))))) 
                  | ((QData)((IData)(__Vtemp_113[(0x07fffffeU 
                                                  & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                                     << 1U))])) 
                     >> (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                        << 6U))))) : vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result);
    vlSelfRef.SoC__DOT___sram_io_fetch_data = (vlSelfRef.SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory
                                               [(0x00001fffU 
                                                 & (IData)(
                                                           (vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
                                                            >> 3U)))] 
                                               & (- (QData)((IData)(
                                                                    (0x0000000000010000ULL 
                                                                     > 
                                                                     (vlSelfRef.SoC__DOT__core__DOT__frontend__DOT__pc 
                                                                      - 0x0000000020000000ULL))))));
    vlSelfRef.SoC__DOT__core__DOT__decode__DOT___GEN 
        = ((0x37U == (0x0000007fU & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
           | (0x17U == (0x0000007fU & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_10 = (((IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd) 
                                                  == 
                                                  (0x0000001fU 
                                                   & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                      >> 0x00000014U))) 
                                                 & (IData)(vlSelfRef.SoC__DOT__core__DOT___writeback_io_wen));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_11 = (((IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd) 
                                                  == 
                                                  (0x0000001fU 
                                                   & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                      >> 0x0000000fU))) 
                                                 & (IData)(vlSelfRef.SoC__DOT__core__DOT___writeback_io_wen));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_0 = ((0x13U 
                                                 == 
                                                 (0x0000007fU 
                                                  & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                | (0x33U 
                                                   == 
                                                   (0x0000007fU 
                                                    & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_5 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd) 
                                                == 
                                                (0x0000001fU 
                                                 & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                    >> 0x0000000fU)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_6 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd) 
                                                == 
                                                (0x0000001fU 
                                                 & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                    >> 0x00000014U)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_7 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rd) 
                                                == 
                                                (0x0000001fU 
                                                 & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                    >> 0x0000000fU)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_8 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rd) 
                                                == 
                                                (0x0000001fU 
                                                 & (vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr 
                                                    >> 0x00000014U)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_13 = (IData)(
                                                        ((0x00005000U 
                                                          == 
                                                          (0x00007000U 
                                                           & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                         & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)));
    vlSelfRef.SoC__DOT__core__DOT___hazard_io_stall 
        = ((~ (IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush)) 
           & (((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_5) 
               & (IData)(__VdfgRegularize_hebeb780c_0_12)) 
              | (((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_6) 
                  & (IData)(__VdfgRegularize_hebeb780c_0_12)) 
                 | ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad) 
                    & (((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_7) 
                        | (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_8)) 
                       & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_3))))));
    vlSelfRef.SoC__DOT__core__DOT__pipe_stall = ((IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_stall) 
                                                 | (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall));
    vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_stall) 
           | (IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush));
}

void VSoC___024root___eval_nba(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_nba\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        VSoC___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void VSoC___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSoC___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool VSoC___024root___eval_phase__act(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_phase__act\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VSoC___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VSoC___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    VSoC___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void VSoC___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool VSoC___024root___eval_phase__nba(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_phase__nba\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = VSoC___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        VSoC___024root___eval_nba(vlSelf);
        VSoC___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void VSoC___024root___eval(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VSoC___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("../../hardware/generated/../../hardware/generated/SoC.sv", 2, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VSoC___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("../../hardware/generated/../../hardware/generated/SoC.sv", 2, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = VSoC___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = VSoC___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void VSoC___024root___eval_debug_assertions(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_debug_assertions\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");
    }
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");
    }
    if (VL_UNLIKELY(((vlSelfRef.io_uart_rx & 0xfeU)))) {
        Verilated::overWidthError("io_uart_rx");
    }
}
#endif  // VL_DEBUG
