// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSoC.h for the primary calling header

#include "VSoC__pch.h"

VL_ATTR_COLD void VSoC___024root___eval_static(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_static\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
}

VL_ATTR_COLD void VSoC___024root___eval_initial(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_initial\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VSoC___024root___eval_final(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_final\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSoC___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VSoC___024root___eval_phase__stl(VSoC___024root* vlSelf);

VL_ATTR_COLD void VSoC___024root___eval_settle(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_settle\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            VSoC___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("../../hardware/generated/../../hardware/generated/SoC.sv", 2, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 10000 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = VSoC___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void VSoC___024root___eval_triggers_vec__stl(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_triggers_vec__stl\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool VSoC___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VSoC___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(VSoC___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool VSoC___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void VSoC___024root___stl_sequent__TOP__0(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___stl_sequent__TOP__0\n"); );
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
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<32>/*1023:0*/ __Vtemp_37;
    VlWide<27>/*863:0*/ __Vtemp_52;
    VlWide<27>/*863:0*/ __Vtemp_67;
    VlWide<53>/*1695:0*/ __Vtemp_68;
    VlWide<64>/*2047:0*/ __Vtemp_99;
    VlWide<16>/*511:0*/ __Vtemp_107;
    // Body
    vlSelfRef.io_uart_tx = vlSelfRef.SoC__DOT__uart__DOT__tx_reg;
    vlSelfRef.SoC__DOT__core__DOT__decode__DOT___GEN 
        = ((0x37U == (0x0000007fU & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
           | (0x17U == (0x0000007fU & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)));
    vlSelfRef.SoC__DOT___core_io_dcache_wdata = (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val 
                                                 << 
                                                 (0x00000038U 
                                                  & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                                                     << 3U)));
    vlSelfRef.SoC__DOT__core__DOT__execute__DOT___bu_io_target 
        = (vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc 
           + vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm);
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
    vlSelfRef.__VdfgRegularize_hebeb780c_0_0 = ((0x13U 
                                                 == 
                                                 (0x0000007fU 
                                                  & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                | (0x33U 
                                                   == 
                                                   (0x0000007fU 
                                                    & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)));
    vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_data 
        = (0x000000ffU & VL_SHIFTL_III(8,8,6, (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val), 
                                       (0x00000038U 
                                        & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                                           << 3U))));
    __Vtemp_2[0U] = (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val);
    __Vtemp_2[1U] = (IData)((vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val 
                             >> 0x00000020U));
    __Vtemp_2[2U] = 0U;
    __Vtemp_2[3U] = 0U;
    VL_SHIFTL_WWI(127,127,6, __Vtemp_3, __Vtemp_2, 
                  (0x00000038U & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                                  << 3U)));
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[0U] 
        = __Vtemp_3[0U];
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[1U] 
        = __Vtemp_3[1U];
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[2U] 
        = __Vtemp_3[2U];
    SoC__DOT__core__DOT__memory__DOT__shiftedStoreData[3U] 
        = (0x7fffffffU & __Vtemp_3[3U]);
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
    SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
        = (((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isAuipc)
             ? vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc
             : vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val) 
           & (- (QData)((IData)((1U & (~ (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLui)))))));
    vlSelfRef.SoC__DOT__core__DOT___writeback_io_wen 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_valid) 
           & (0U != (IData)(vlSelfRef.SoC__DOT__core__DOT__mem_wb__DOT__reg_rd)));
    SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
        = (((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_useImm) 
            | ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLui) 
               | (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isAuipc)))
            ? vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_imm
            : vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val);
    vlSelfRef.__VdfgRegularize_hebeb780c_0_3 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_valid) 
                                                & (0U 
                                                   != (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_rd)));
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
    __VdfgRegularize_hebeb780c_0_12 = ((0U != (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd)) 
                                       & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad) 
                                          & (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid)));
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
    SoC__DOT__core__DOT__execute__DOT__bu__DOT___io_taken_T_7 
        = ((0U == (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_brOp)) 
           & (vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val 
              == vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val));
    __VdfgRegularize_hebeb780c_0_2 = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJal) 
                                      | (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr));
    SoC__DOT__sram_sel = ((0U != (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                  >> 0x0000001dU)) 
                          & (0x0000000020010000ULL 
                             > vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result));
    SoC__DOT___core_io_dcache_valid = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_valid) 
                                       & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad) 
                                          | (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore)));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_13 = (IData)(
                                                        ((0x00005000U 
                                                          == 
                                                          (0x00007000U 
                                                           & vlSelfRef.SoC__DOT__core__DOT__if_id__DOT__reg_instr)) 
                                                         & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)));
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
    __Vtemp_37[0U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              + SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_37[1U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               + SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_37[2U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                              - SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2));
    __Vtemp_37[3U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                               - SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2) 
                              >> 0x00000020U));
    __Vtemp_37[4U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              & SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_37[5U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               & SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_37[6U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              | SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_37[7U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               | SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_37[8U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                              ^ SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1));
    __Vtemp_37[9U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2 
                               ^ SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1) 
                              >> 0x00000020U));
    __Vtemp_37[10U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                               << (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_37[11U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                                << (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_37[12U] = (IData)((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                               >> (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_37[13U] = (IData)(((SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                                >> (0x0000003fU & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_37[14U] = (IData)(VL_SHIFTRS_QQI(64,64,6, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, 
                                             (0x0000003fU 
                                              & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_37[15U] = (IData)((VL_SHIFTRS_QQI(64,64,6, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, 
                                              (0x0000003fU 
                                               & (IData)(SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_37[16U] = (IData)((QData)((IData)(VL_LTS_IQQ(64, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))));
    __Vtemp_37[17U] = (IData)(((QData)((IData)(VL_LTS_IQQ(64, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1, SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2))) 
                               >> 0x00000020U));
    __Vtemp_37[18U] = (SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs1 
                       < SoC__DOT__core__DOT__execute__DOT____Vcellinp__alu__io_rs2);
    __Vtemp_37[19U] = 0U;
    __Vtemp_37[20U] = 0U;
    __Vtemp_37[21U] = 0U;
    __Vtemp_37[22U] = 0U;
    __Vtemp_37[23U] = 0U;
    __Vtemp_37[24U] = 0U;
    __Vtemp_37[25U] = 0U;
    __Vtemp_37[26U] = 0U;
    __Vtemp_37[27U] = 0U;
    __Vtemp_37[28U] = 0U;
    __Vtemp_37[29U] = 0U;
    __Vtemp_37[30U] = 0U;
    __Vtemp_37[31U] = 0U;
    vlSelfRef.SoC__DOT__core__DOT___execute_io_out_result 
        = ((IData)(__VdfgRegularize_hebeb780c_0_2) ? 
           (4ULL + vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_pc)
            : (((QData)((IData)(__Vtemp_37[(((IData)(0x0000003fU) 
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
                    : ((QData)((IData)(__Vtemp_37[(
                                                   ((IData)(0x0000001fU) 
                                                    + 
                                                    ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                                     << 6U)) 
                                                   >> 5U)])) 
                       << ((IData)(0x00000020U) - (0x0000001fU 
                                                   & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                                      << 6U))))) 
                  | ((QData)((IData)(__Vtemp_37[(0x07fffffeU 
                                                 & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                                    << 1U))])) 
                     >> (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp) 
                                        << 6U))))));
    vlSelfRef.SoC__DOT__core__DOT____Vcellinp__forward__io_ex_wen 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_valid) 
           | (IData)(__VdfgRegularize_hebeb780c_0_2));
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
    SoC__DOT____Vcellinp__sram__io_wen = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore) 
                                          & (IData)(SoC__DOT__sram_sel));
    SoC__DOT__uart_write = ((IData)(SoC__DOT___core_io_dcache_valid) 
                            & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore) 
                               & ((0U != (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                          >> 0x0000001cU)) 
                                  & (0x0000000010001000ULL 
                                     > vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result))));
    __Vtemp_52[23U] = ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
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
    __Vtemp_52[24U] = (((((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_30) 
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
    __Vtemp_52[25U] = (((((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_31) 
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
    __Vtemp_52[26U] = ((0x000000ffU & (((0x000003ffU 
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
    __Vtemp_67[23U] = ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
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
    __Vtemp_67[24U] = (((((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_14) 
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
    __Vtemp_67[25U] = (((((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_15) 
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
    __Vtemp_67[26U] = ((0x000000ffU & (((0x000003ffU 
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
    __Vtemp_68[0U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_0);
    __Vtemp_68[1U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_1) 
                       << 0x00000015U) | (IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_0 
                                                  >> 0x00000020U)));
    __Vtemp_68[2U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_1) 
                       >> 0x0000000bU) | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_1 
                                                   >> 0x00000020U)) 
                                          << 0x00000015U));
    __Vtemp_68[3U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_2) 
                       << 0x0000000aU) | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_1 
                                                   >> 0x00000020U)) 
                                          >> 0x0000000bU));
    __Vtemp_68[4U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_2) 
                       >> 0x00000016U) | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_3) 
                                           << 0x0000001fU) 
                                          | ((IData)(
                                                     (vlSelfRef.SoC__DOT__dcache__DOT__tags_2 
                                                      >> 0x00000020U)) 
                                             << 0x0000000aU)));
    __Vtemp_68[5U] = (((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_3) 
                                       >> 1U)) | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_2 
                                                           >> 0x00000020U)) 
                                                  >> 0x00000016U)) 
                      | ((0x7ffffc00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_3) 
                                         >> 1U)) | 
                         ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_3 
                                   >> 0x00000020U)) 
                          << 0x0000001fU)));
    __Vtemp_68[6U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_4) 
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
    __Vtemp_68[7U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_4) 
                       >> 0x0000000cU) | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_4 
                                                   >> 0x00000020U)) 
                                          << 0x00000014U));
    __Vtemp_68[8U] = (((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_5) 
                                       << 9U)) | ((IData)(
                                                          (vlSelfRef.SoC__DOT__dcache__DOT__tags_4 
                                                           >> 0x00000020U)) 
                                                  >> 0x0000000cU)) 
                      | (0xfff00000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_5) 
                                        << 9U)));
    __Vtemp_68[9U] = ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_5) 
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
    __Vtemp_68[10U] = (((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_6) 
                                        >> 2U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_5 
                                                            >> 0x00000020U)) 
                                                   >> 0x00000017U)) 
                       | ((0x3ff00000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_6) 
                                          >> 2U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_6 
                                    >> 0x00000020U)) 
                           << 0x0000001eU)));
    __Vtemp_68[11U] = (((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_7) 
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
    __Vtemp_68[12U] = (((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_7) 
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
    __Vtemp_68[13U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_8) 
                        << 8U) | (((0x000003ffU & ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                            >> 0x00000020U)) 
                                                   >> 1U)) 
                                   | (0x7ffffc00U & 
                                      ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_7 
                                                >> 0x00000020U)) 
                                       >> 1U))) >> 0x0000000cU));
    __Vtemp_68[14U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_8) 
                        >> 0x00000018U) | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_9) 
                                            << 0x0000001dU) 
                                           | ((IData)(
                                                      (vlSelfRef.SoC__DOT__dcache__DOT__tags_8 
                                                       >> 0x00000020U)) 
                                              << 8U)));
    __Vtemp_68[15U] = (((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_9) 
                                        >> 3U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_8 
                                                            >> 0x00000020U)) 
                                                   >> 0x00000018U)) 
                       | ((0x1fffff00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_9) 
                                          >> 3U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_9 
                                    >> 0x00000020U)) 
                           << 0x0000001dU)));
    __Vtemp_68[16U] = ((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_9 
                                                >> 0x00000020U)) 
                                       >> 3U)) | (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_10) 
                                                   << 0x00000012U) 
                                                  | (0x1fffff00U 
                                                     & ((IData)(
                                                                (vlSelfRef.SoC__DOT__dcache__DOT__tags_9 
                                                                 >> 0x00000020U)) 
                                                        >> 3U))));
    __Vtemp_68[17U] = ((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_10) 
                                       >> 0x0000000eU)) 
                       | ((0x0003ff00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_10) 
                                          >> 0x0000000eU)) 
                          | ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_10 
                                      >> 0x00000020U)) 
                             << 0x00000012U)));
    __Vtemp_68[18U] = (((0x00000080U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_11) 
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
    __Vtemp_68[19U] = (((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_11) 
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
    __Vtemp_68[20U] = (((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_12) 
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
    __Vtemp_68[21U] = ((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_12 
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
    __Vtemp_68[22U] = (((((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_13) 
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
    __Vtemp_68[23U] = __Vtemp_67[23U];
    __Vtemp_68[24U] = __Vtemp_67[24U];
    __Vtemp_68[25U] = __Vtemp_67[25U];
    __Vtemp_68[26U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_16) 
                        << 0x00000010U) | __Vtemp_67[26U]);
    __Vtemp_68[27U] = (((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_16) 
                        >> 0x00000010U) | ((IData)(
                                                   (vlSelfRef.SoC__DOT__dcache__DOT__tags_16 
                                                    >> 0x00000020U)) 
                                           << 0x00000010U));
    __Vtemp_68[28U] = (((0x0000ffe0U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_17) 
                                        << 5U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_16 
                                                            >> 0x00000020U)) 
                                                   >> 0x00000010U)) 
                       | (0xffff0000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_17) 
                                         << 5U)));
    __Vtemp_68[29U] = ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_17) 
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
    __Vtemp_68[30U] = (((0x0000ffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_18) 
                                        >> 6U)) | ((IData)(
                                                           (vlSelfRef.SoC__DOT__dcache__DOT__tags_17 
                                                            >> 0x00000020U)) 
                                                   >> 0x0000001bU)) 
                       | ((0x03ff0000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_18) 
                                          >> 6U)) | 
                          ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_18 
                                    >> 0x00000020U)) 
                           << 0x0000001aU)));
    __Vtemp_68[31U] = (((0x00008000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_19) 
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
    __Vtemp_68[32U] = (((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_19) 
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
    __Vtemp_68[33U] = (((0x0000fff0U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_20) 
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
    __Vtemp_68[34U] = ((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_20) 
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
    __Vtemp_68[35U] = (((((0x000ffe00U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
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
    __Vtemp_68[36U] = ((((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_21) 
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
    __Vtemp_68[37U] = (((((0x000fffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_22) 
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
    __Vtemp_68[38U] = (((((0x00080000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
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
    __Vtemp_68[39U] = ((((((0x000003ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_23) 
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
    __Vtemp_68[40U] = (((0x0000ffffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_24) 
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
    __Vtemp_68[41U] = (((0x0000e000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_25) 
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
    __Vtemp_68[42U] = (((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_25) 
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
    __Vtemp_68[43U] = ((((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_25 
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
    __Vtemp_68[44U] = ((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_26) 
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
    __Vtemp_68[45U] = (((((0x00000080U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_27) 
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
    __Vtemp_68[46U] = (((0x0000f000U & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_28) 
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
    __Vtemp_68[47U] = (((((0x000000ffU & ((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_28) 
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
    __Vtemp_68[48U] = ((((0x000000ffU & ((IData)((vlSelfRef.SoC__DOT__dcache__DOT__tags_28 
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
    __Vtemp_68[49U] = ((0x0000ffffU & (((((IData)(vlSelfRef.SoC__DOT__dcache__DOT__tags_29) 
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
                                       >> 8U)) | (__Vtemp_52[23U] 
                                                  << 0x00000010U));
    __Vtemp_68[50U] = ((__Vtemp_52[23U] >> 0x00000010U) 
                       | (__Vtemp_52[24U] << 0x00000010U));
    __Vtemp_68[51U] = ((__Vtemp_52[24U] >> 0x00000010U) 
                       | (__Vtemp_52[25U] << 0x00000010U));
    __Vtemp_68[52U] = ((__Vtemp_52[25U] >> 0x00000010U) 
                       | (__Vtemp_52[26U] << 0x00000010U));
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
                                                   & ((((QData)((IData)(__Vtemp_68
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
                                                           ((QData)((IData)(__Vtemp_68
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
                                                          | ((QData)((IData)(__Vtemp_68
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
    SoC__DOT__sram_io_valid = ((IData)(SoC__DOT___core_io_dcache_valid) 
                               & (IData)(SoC__DOT__sram_sel));
    vlSelfRef.__VdfgRegularize_hebeb780c_0_14 = ((0U 
                                                  != (IData)(vlSelfRef.SoC__DOT__core__DOT__id_ex__DOT__reg_rd)) 
                                                 & (IData)(vlSelfRef.SoC__DOT__core__DOT____Vcellinp__forward__io_ex_wen));
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
    vlSelfRef.SoC__DOT____Vcellinp__uart__io_tx_valid 
        = ((0U == (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
           & (IData)(SoC__DOT__uart_write));
    vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall 
        = ((0U != (IData)(vlSelfRef.SoC__DOT__uart__DOT__state)) 
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
    vlSelfRef.SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_stall) 
           | (IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_flush));
    vlSelfRef.SoC__DOT__core__DOT__pipe_stall = ((IData)(vlSelfRef.SoC__DOT__core__DOT___hazard_io_stall) 
                                                 | (IData)(vlSelfRef.SoC__DOT____Vcellinp__core__io_dcache_stall));
    __Vtemp_99[0U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_0);
    __Vtemp_99[1U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_0 
                              >> 0x00000020U));
    __Vtemp_99[2U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_1);
    __Vtemp_99[3U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_1 
                              >> 0x00000020U));
    __Vtemp_99[4U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_2);
    __Vtemp_99[5U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_2 
                              >> 0x00000020U));
    __Vtemp_99[6U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_3);
    __Vtemp_99[7U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_3 
                              >> 0x00000020U));
    __Vtemp_99[8U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_4);
    __Vtemp_99[9U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_4 
                              >> 0x00000020U));
    __Vtemp_99[10U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_5);
    __Vtemp_99[11U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_5 
                               >> 0x00000020U));
    __Vtemp_99[12U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_6);
    __Vtemp_99[13U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_6 
                               >> 0x00000020U));
    __Vtemp_99[14U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_7);
    __Vtemp_99[15U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_7 
                               >> 0x00000020U));
    __Vtemp_99[16U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_8);
    __Vtemp_99[17U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_8 
                               >> 0x00000020U));
    __Vtemp_99[18U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_9);
    __Vtemp_99[19U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_9 
                               >> 0x00000020U));
    __Vtemp_99[20U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_10);
    __Vtemp_99[21U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_10 
                               >> 0x00000020U));
    __Vtemp_99[22U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_11);
    __Vtemp_99[23U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_11 
                               >> 0x00000020U));
    __Vtemp_99[24U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_12);
    __Vtemp_99[25U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_12 
                               >> 0x00000020U));
    __Vtemp_99[26U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_13);
    __Vtemp_99[27U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_13 
                               >> 0x00000020U));
    __Vtemp_99[28U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_14);
    __Vtemp_99[29U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_14 
                               >> 0x00000020U));
    __Vtemp_99[30U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_15);
    __Vtemp_99[31U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_15 
                               >> 0x00000020U));
    __Vtemp_99[32U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_16);
    __Vtemp_99[33U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_16 
                               >> 0x00000020U));
    __Vtemp_99[34U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_17);
    __Vtemp_99[35U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_17 
                               >> 0x00000020U));
    __Vtemp_99[36U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_18);
    __Vtemp_99[37U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_18 
                               >> 0x00000020U));
    __Vtemp_99[38U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_19);
    __Vtemp_99[39U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_19 
                               >> 0x00000020U));
    __Vtemp_99[40U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_20);
    __Vtemp_99[41U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_20 
                               >> 0x00000020U));
    __Vtemp_99[42U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_21);
    __Vtemp_99[43U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_21 
                               >> 0x00000020U));
    __Vtemp_99[44U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_22);
    __Vtemp_99[45U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_22 
                               >> 0x00000020U));
    __Vtemp_99[46U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_23);
    __Vtemp_99[47U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_23 
                               >> 0x00000020U));
    __Vtemp_99[48U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_24);
    __Vtemp_99[49U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_24 
                               >> 0x00000020U));
    __Vtemp_99[50U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_25);
    __Vtemp_99[51U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_25 
                               >> 0x00000020U));
    __Vtemp_99[52U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_26);
    __Vtemp_99[53U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_26 
                               >> 0x00000020U));
    __Vtemp_99[54U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_27);
    __Vtemp_99[55U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_27 
                               >> 0x00000020U));
    __Vtemp_99[56U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_28);
    __Vtemp_99[57U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_28 
                               >> 0x00000020U));
    __Vtemp_99[58U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_29);
    __Vtemp_99[59U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_29 
                               >> 0x00000020U));
    __Vtemp_99[60U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_30);
    __Vtemp_99[61U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_30 
                               >> 0x00000020U));
    __Vtemp_99[62U] = (IData)(vlSelfRef.SoC__DOT__dcache__DOT__data_31);
    __Vtemp_99[63U] = (IData)((vlSelfRef.SoC__DOT__dcache__DOT__data_31 
                               >> 0x00000020U));
    SoC__DOT____Vcellinp__core__io_dcache_rdata = ((IData)(SoC__DOT__sram_sel)
                                                    ? vlSelfRef.SoC__DOT___sram_io_rdata
                                                    : 
                                                   ((IData)(vlSelfRef.SoC__DOT____Vcellinp__dcache__io_mem_valid)
                                                     ? vlSelfRef.SoC__DOT___sram_io_rdata
                                                     : 
                                                    ((((QData)((IData)(__Vtemp_99
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
                                                      | (QData)((IData)(__Vtemp_99
                                                                        [
                                                                        (0x0000003eU 
                                                                         & ((IData)(
                                                                                (vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result 
                                                                                >> 6U)) 
                                                                            << 1U))]))) 
                                                     & (- (QData)((IData)(
                                                                          ((~ (IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore)) 
                                                                           & (IData)(vlSelfRef.SoC__DOT__dcache__DOT__hit))))))));
    SoC__DOT__core__DOT__memory__DOT__shiftedLoad = 
        (SoC__DOT____Vcellinp__core__io_dcache_rdata 
         >> (0x00000038U & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result) 
                            << 3U)));
    __Vtemp_107[0U] = (IData)((((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                               >> 7U)))))) 
                                << 8U) | (QData)((IData)(
                                                         (0x000000ffU 
                                                          & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))));
    __Vtemp_107[1U] = (IData)(((((- (QData)((IData)(
                                                    (1U 
                                                     & (IData)(
                                                               (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                                >> 7U)))))) 
                                 << 8U) | (QData)((IData)(
                                                          (0x000000ffU 
                                                           & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))) 
                               >> 0x00000020U));
    __Vtemp_107[2U] = (IData)((((- (QData)((IData)(
                                                   (1U 
                                                    & (IData)(
                                                              (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                               >> 0x0000000fU)))))) 
                                << 0x00000010U) | (QData)((IData)(
                                                                  (0x0000ffffU 
                                                                   & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))));
    __Vtemp_107[3U] = (IData)(((((- (QData)((IData)(
                                                    (1U 
                                                     & (IData)(
                                                               (SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                                >> 0x0000000fU)))))) 
                                 << 0x00000010U) | (QData)((IData)(
                                                                   (0x0000ffffU 
                                                                    & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad))))) 
                               >> 0x00000020U));
    __Vtemp_107[4U] = (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad);
    __Vtemp_107[5U] = (- (IData)((1U & (IData)((SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                                                >> 0x0000001fU)))));
    __Vtemp_107[6U] = (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad);
    __Vtemp_107[7U] = (IData)((SoC__DOT__core__DOT__memory__DOT__shiftedLoad 
                               >> 0x00000020U));
    __Vtemp_107[8U] = (IData)((QData)((IData)((0x000000ffU 
                                               & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))));
    __Vtemp_107[9U] = (IData)(((QData)((IData)((0x000000ffU 
                                                & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))) 
                               >> 0x00000020U));
    __Vtemp_107[10U] = (IData)((QData)((IData)((0x0000ffffU 
                                                & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))));
    __Vtemp_107[11U] = (IData)(((QData)((IData)((0x0000ffffU 
                                                 & (IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)))) 
                                >> 0x00000020U));
    __Vtemp_107[12U] = (IData)((QData)((IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)));
    __Vtemp_107[13U] = (IData)(((QData)((IData)(SoC__DOT__core__DOT__memory__DOT__shiftedLoad)) 
                                >> 0x00000020U));
    __Vtemp_107[14U] = (IData)(SoC__DOT____Vcellinp__core__io_dcache_rdata);
    __Vtemp_107[15U] = (IData)((SoC__DOT____Vcellinp__core__io_dcache_rdata 
                                >> 0x00000020U));
    vlSelfRef.SoC__DOT__core__DOT___memory_io_out_result 
        = ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad)
            ? (((QData)((IData)(__Vtemp_107[(((IData)(0x0000003fU) 
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
                    : ((QData)((IData)(__Vtemp_107[
                                       (((IData)(0x0000001fU) 
                                         + ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                            << 6U)) 
                                        >> 5U)])) << 
                       ((IData)(0x00000020U) - (0x0000001fU 
                                                & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                                   << 6U))))) 
                  | ((QData)((IData)(__Vtemp_107[(0x07fffffeU 
                                                  & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                                     << 1U))])) 
                     >> (0x0000001fU & ((IData)(vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp) 
                                        << 6U))))) : vlSelfRef.SoC__DOT__core__DOT__ex_mem__DOT__reg_result);
}

VL_ATTR_COLD void VSoC___024root___eval_stl(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_stl\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        VSoC___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool VSoC___024root___eval_phase__stl(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___eval_phase__stl\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    VSoC___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VSoC___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = VSoC___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        VSoC___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool VSoC___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VSoC___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(VSoC___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VSoC___024root___ctor_var_reset(VSoC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSoC___024root___ctor_var_reset\n"); );
    VSoC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5452235342940299466ull);
    vlSelf->reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9928399931838511862ull);
    vlSelf->io_uart_tx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4644386009409362979ull);
    vlSelf->io_uart_rx = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3620444692789605001ull);
    vlSelf->SoC__DOT___sram_io_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6961728568044507178ull);
    vlSelf->SoC__DOT___sram_io_fetch_data = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8333102665262242079ull);
    vlSelf->SoC__DOT___core_io_dcache_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14846582703615113736ull);
    vlSelf->SoC__DOT____Vcellinp__core__io_dcache_stall = 0;
    vlSelf->SoC__DOT____Vcellinp__dcache__io_mem_valid = 0;
    vlSelf->SoC__DOT____Vcellinp__uart__io_tx_valid = 0;
    vlSelf->SoC__DOT____Vcellinp__uart__io_tx_data = 0;
    vlSelf->SoC__DOT__core__DOT___hazard_io_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17693292520208110207ull);
    vlSelf->SoC__DOT__core__DOT___hazard_io_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3786746361760969285ull);
    vlSelf->SoC__DOT__core__DOT___writeback_io_wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5810824165309249088ull);
    vlSelf->SoC__DOT__core__DOT___memory_io_out_result = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16927002863438806215ull);
    vlSelf->SoC__DOT__core__DOT___execute_io_out_result = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4991493033924743239ull);
    vlSelf->SoC__DOT__core__DOT__pipe_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6300994758896727246ull);
    vlSelf->SoC__DOT__core__DOT____Vcellinp__forward__io_ex_wen = 0;
    vlSelf->SoC__DOT__core__DOT____Vcellinp__id_ex__io_flush = 0;
    vlSelf->SoC__DOT__core__DOT__frontend__DOT__pc = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16396566024321409485ull);
    vlSelf->SoC__DOT__core__DOT__decode__DOT___GEN = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13499310919763716318ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_0 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17223082169374425441ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_1 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17251800031171739555ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_2 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5332008067796466554ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_3 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12635369760847186849ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_4 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14928397319114149224ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_5 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3447946563460796429ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_6 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16473132922331730676ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_7 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4553340958956543163ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_8 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12989157617306992381ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_9 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14149730210274116925ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_10 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14685391863242542770ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_11 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6634673281833113273ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_12 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7751127858911363435ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_13 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4413953197617116838ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_14 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6527495047603485288ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_15 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10069188055475730353ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_16 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15437057843665731471ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_17 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9206729512805820059ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_18 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3273005345024262550ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_19 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2076270078574802647ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_20 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9842970943988884965ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_21 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11913887330689752743ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_22 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15397894277919214927ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_23 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1581382739264305756ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_24 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7797428242909052521ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_25 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12569804455549988902ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_26 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 18163314830525023674ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_27 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5198134418940121808ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_28 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 18026974405213221879ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_29 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5904824162538409843ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_30 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7631024880338905394ull);
    vlSelf->SoC__DOT__core__DOT__regfile__DOT__regs_31 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5572278347975171340ull);
    VL_SCOPED_RAND_RESET_W(2048, vlSelf->SoC__DOT__core__DOT__regfile__DOT___GEN, __VscopeHash, 2816505357236235287ull);
    vlSelf->SoC__DOT__core__DOT__execute__DOT___bu_io_target = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13865751033931900125ull);
    vlSelf->SoC__DOT__core__DOT__if_id__DOT__reg_pc = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9360229524476308093ull);
    vlSelf->SoC__DOT__core__DOT__if_id__DOT__reg_instr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14830057112945945181ull);
    vlSelf->SoC__DOT__core__DOT__if_id__DOT__reg_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11388122395576732704ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_pc = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10175391614030346225ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_rs1_val = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15642656559061404167ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_rs2_val = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 144781361472342714ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_imm = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2460849636728584863ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 10075710551914631639ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_aluOp = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 14019697909680349786ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_brOp = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10362734704406708542ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_memOp = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12285807655619796259ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_useImm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14084602839453041121ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_isLoad = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18078195582779576671ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_isStore = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13512277803635945482ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_isBranch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17958148514003807302ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_isJal = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10678771929241955246ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_isJalr = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6018833627406235200ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_isLui = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2947825373078868553ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_isAuipc = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10457938406328483288ull);
    vlSelf->SoC__DOT__core__DOT__id_ex__DOT__reg_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10578963487193432852ull);
    vlSelf->SoC__DOT__core__DOT__ex_mem__DOT__reg_result = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15293222773294031805ull);
    vlSelf->SoC__DOT__core__DOT__ex_mem__DOT__reg_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17651987875611641443ull);
    vlSelf->SoC__DOT__core__DOT__ex_mem__DOT__reg_rs2_val = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11875495035346933944ull);
    vlSelf->SoC__DOT__core__DOT__ex_mem__DOT__reg_memOp = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17409256290735198879ull);
    vlSelf->SoC__DOT__core__DOT__ex_mem__DOT__reg_isLoad = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11299136062783659055ull);
    vlSelf->SoC__DOT__core__DOT__ex_mem__DOT__reg_isStore = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 925713045903312315ull);
    vlSelf->SoC__DOT__core__DOT__ex_mem__DOT__reg_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8072896855309685963ull);
    vlSelf->SoC__DOT__core__DOT__mem_wb__DOT__reg_result = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15220796609452519028ull);
    vlSelf->SoC__DOT__core__DOT__mem_wb__DOT__reg_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1920902620189458791ull);
    vlSelf->SoC__DOT__core__DOT__mem_wb__DOT__reg_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1676182453846589513ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11599685096677362187ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4009483776753240371ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2118108541973563787ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14788347025727938569ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17692652809104092903ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14867175437971386723ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11591373729896148257ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12704381790379648997ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4906609296595959355ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_9 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16070535393014482747ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_10 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10309432733558703428ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_11 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8791905874825630688ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_12 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7970190583931269549ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_13 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12359349516862772797ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_14 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10486154360076629358ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_15 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16054452316136418118ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_16 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3374272480425665476ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_17 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9602642184155365802ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3940765982009977803ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_19 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3172119274954480223ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_20 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7455789628638366741ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_21 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6588086194759063856ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_22 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2431873582408292192ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_23 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3817101035761632666ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_24 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11680125364645007970ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_25 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7092723538691195084ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_26 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2713801156837482182ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_27 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1381135423948811492ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_28 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8899846491514568921ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_29 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12538535084391371354ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_30 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15823439397884697998ull);
    vlSelf->SoC__DOT__dcache__DOT__valid_31 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13902017112195005440ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_0 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 3921705849955267739ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_1 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 2416349795684437287ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_2 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 420975764062077049ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_3 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 17466014703689337994ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_4 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 1221950828357326397ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_5 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 3725582726055316290ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_6 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 13493645292845070514ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_7 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 181632289277503682ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_8 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 11934186122201718918ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_9 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 14033427501307119421ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_10 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 9757318612871712377ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_11 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 2766355907456455487ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_12 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 6593277625590493190ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_13 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 10613478889239030072ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_14 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 9497156219195819952ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_15 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 13420103045313774431ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_16 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 17339649846959081911ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_17 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 6314431410316473536ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_18 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 10492401659345861815ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_19 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 12067742963855739000ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_20 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 3322163179161070633ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_21 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 7512206112211504704ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_22 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 17558109309382333491ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_23 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 14580233657664442789ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_24 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 2131404724063190520ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_25 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 11595485081689321846ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_26 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 16198074597827569548ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_27 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 9624825060117560923ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_28 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 6593776814161787786ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_29 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 789798591797592169ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_30 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 15310851742140094678ull);
    vlSelf->SoC__DOT__dcache__DOT__tags_31 = VL_SCOPED_RAND_RESET_Q(53, __VscopeHash, 4856826327850363078ull);
    vlSelf->SoC__DOT__dcache__DOT__data_0 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1434074772391247865ull);
    vlSelf->SoC__DOT__dcache__DOT__data_1 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3790618971721723077ull);
    vlSelf->SoC__DOT__dcache__DOT__data_2 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10352038085542799666ull);
    vlSelf->SoC__DOT__dcache__DOT__data_3 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 621824162411491113ull);
    vlSelf->SoC__DOT__dcache__DOT__data_4 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17752150796397519007ull);
    vlSelf->SoC__DOT__dcache__DOT__data_5 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10269248791702259602ull);
    vlSelf->SoC__DOT__dcache__DOT__data_6 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1209072516831375149ull);
    vlSelf->SoC__DOT__dcache__DOT__data_7 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12603314668408971799ull);
    vlSelf->SoC__DOT__dcache__DOT__data_8 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 785046148046469529ull);
    vlSelf->SoC__DOT__dcache__DOT__data_9 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16293835511533236839ull);
    vlSelf->SoC__DOT__dcache__DOT__data_10 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5865511721774445116ull);
    vlSelf->SoC__DOT__dcache__DOT__data_11 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5435051284147962639ull);
    vlSelf->SoC__DOT__dcache__DOT__data_12 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15248180307569073526ull);
    vlSelf->SoC__DOT__dcache__DOT__data_13 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9260719046821575354ull);
    vlSelf->SoC__DOT__dcache__DOT__data_14 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 18209322182466653736ull);
    vlSelf->SoC__DOT__dcache__DOT__data_15 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7755862181121957998ull);
    vlSelf->SoC__DOT__dcache__DOT__data_16 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12158613822430050498ull);
    vlSelf->SoC__DOT__dcache__DOT__data_17 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1474457380547025907ull);
    vlSelf->SoC__DOT__dcache__DOT__data_18 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2710559615135886742ull);
    vlSelf->SoC__DOT__dcache__DOT__data_19 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17188366245747160820ull);
    vlSelf->SoC__DOT__dcache__DOT__data_20 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13717005152268317453ull);
    vlSelf->SoC__DOT__dcache__DOT__data_21 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5621611096264058212ull);
    vlSelf->SoC__DOT__dcache__DOT__data_22 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17428702782133893357ull);
    vlSelf->SoC__DOT__dcache__DOT__data_23 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 11924615754508872151ull);
    vlSelf->SoC__DOT__dcache__DOT__data_24 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14093893853674580823ull);
    vlSelf->SoC__DOT__dcache__DOT__data_25 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 1847871070741697134ull);
    vlSelf->SoC__DOT__dcache__DOT__data_26 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 4895245536861235932ull);
    vlSelf->SoC__DOT__dcache__DOT__data_27 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 18069376537345535711ull);
    vlSelf->SoC__DOT__dcache__DOT__data_28 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15222348560371366602ull);
    vlSelf->SoC__DOT__dcache__DOT__data_29 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6383764211289961097ull);
    vlSelf->SoC__DOT__dcache__DOT__data_30 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2535153557573860142ull);
    vlSelf->SoC__DOT__dcache__DOT__data_31 = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2576051901614835815ull);
    vlSelf->SoC__DOT__dcache__DOT__hit = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5815041322532302797ull);
    vlSelf->SoC__DOT__uart__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5459168993381473695ull);
    vlSelf->SoC__DOT__uart__DOT__baud_cnt = VL_SCOPED_RAND_RESET_I(9, __VscopeHash, 18283441968063917430ull);
    vlSelf->SoC__DOT__uart__DOT__bit_cnt = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12576474750946645127ull);
    vlSelf->SoC__DOT__uart__DOT__shift_reg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7490828201602343438ull);
    vlSelf->SoC__DOT__uart__DOT__tx_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15698796562298902642ull);
    vlSelf->SoC__DOT__sram__DOT__mergedWord = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 16831988893129218046ull);
    vlSelf->SoC__DOT__sram__DOT___GEN = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8353523161799409030ull);
    for (int __Vi0 = 0; __Vi0 < 8192; ++__Vi0) {
        vlSelf->SoC__DOT__sram__DOT__mem_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8642485636215329078ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8192; ++__Vi0) {
        vlSelf->SoC__DOT__sram__DOT__fetch_mem_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7800293572487707024ull);
    }
    vlSelf->__VdfgRegularize_hebeb780c_0_0 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_3 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_5 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_6 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_7 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_8 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_10 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_11 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_13 = 0;
    vlSelf->__VdfgRegularize_hebeb780c_0_14 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
