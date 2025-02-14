// RUN: p4mlir-translate --typeinference-only %s | FileCheck %s

// NOTE: Assertions have been autogenerated by utils/generate-test-checks.py

action shl_shr() {
    bit<32> u32i_value = 1;
    int<32> s32i_value = 2;
    bit<8> shift = 3;

    // shl
    bit<32> u32i_shl_u8i = u32i_value << shift;
    bit<32> u32i_shl_int = u32i_value << 1;

    int<32> s32i_shl_u8i = s32i_value << shift;
    int<32> s32i_shl_int = s32i_value << 1;

    const int int_shl_int = 1 << 2;

    // shr
    bit<32> u32i_shr_u8i = u32i_value >> shift;
    bit<32> u32i_shr_int = u32i_value >> 1;

    int<32> s32i_shr_u8i = s32i_value >> shift;
    int<32> s32i_shr_int = s32i_value >> 1;

    const int int_shr_int = 1 >> 2;
}

// CHECK: #[[$ATTR_0:.+]] = #p4hir.int<0> : !infint
// CHECK: #[[$ATTR_1:.+]] = #p4hir.int<1> : !b32i
// CHECK: #[[$ATTR_2:.+]] = #p4hir.int<1> : !infint
// CHECK: #[[$ATTR_3:.+]] = #p4hir.int<2> : !i32i
// CHECK: #[[$ATTR_4:.+]] = #p4hir.int<3> : !b8i
// CHECK: #[[$ATTR_5:.+]] = #p4hir.int<4> : !infint
// CHECK-LABEL:   p4hir.func action @shl_shr() {
// CHECK:           %[[VAL_0:.*]] = p4hir.const #[[$ATTR_1]]
// CHECK:           %[[VAL_1:.*]] = p4hir.cast(%[[VAL_0]] : !b32i) : !b32i
// CHECK:           %[[VAL_2:.*]] = p4hir.variable ["u32i_value", init] : <!b32i>
// CHECK:           p4hir.assign %[[VAL_1]], %[[VAL_2]] : <!b32i>
// CHECK:           %[[VAL_3:.*]] = p4hir.const #[[$ATTR_3]]
// CHECK:           %[[VAL_4:.*]] = p4hir.cast(%[[VAL_3]] : !i32i) : !i32i
// CHECK:           %[[VAL_5:.*]] = p4hir.variable ["s32i_value", init] : <!i32i>
// CHECK:           p4hir.assign %[[VAL_4]], %[[VAL_5]] : <!i32i>
// CHECK:           %[[VAL_6:.*]] = p4hir.const #[[$ATTR_4]]
// CHECK:           %[[VAL_7:.*]] = p4hir.cast(%[[VAL_6]] : !b8i) : !b8i
// CHECK:           %[[VAL_8:.*]] = p4hir.variable ["shift", init] : <!b8i>
// CHECK:           p4hir.assign %[[VAL_7]], %[[VAL_8]] : <!b8i>
// CHECK:           %[[VAL_9:.*]] = p4hir.read %[[VAL_2]] : <!b32i>
// CHECK:           %[[VAL_10:.*]] = p4hir.read %[[VAL_8]] : <!b8i>
// CHECK:           %[[VAL_11:.*]] = p4hir.shl(%[[VAL_9]] : !b32i, %[[VAL_10]] : !b8i) : !b32i
// CHECK:           %[[VAL_12:.*]] = p4hir.variable ["u32i_shl_u8i", init] : <!b32i>
// CHECK:           p4hir.assign %[[VAL_11]], %[[VAL_12]] : <!b32i>
// CHECK:           %[[VAL_13:.*]] = p4hir.const #[[$ATTR_2]]
// CHECK:           %[[VAL_14:.*]] = p4hir.read %[[VAL_2]] : <!b32i>
// CHECK:           %[[VAL_15:.*]] = p4hir.shl(%[[VAL_14]] : !b32i, %[[VAL_13]] : !infint) : !b32i
// CHECK:           %[[VAL_16:.*]] = p4hir.variable ["u32i_shl_int", init] : <!b32i>
// CHECK:           p4hir.assign %[[VAL_15]], %[[VAL_16]] : <!b32i>
// CHECK:           %[[VAL_17:.*]] = p4hir.read %[[VAL_5]] : <!i32i>
// CHECK:           %[[VAL_18:.*]] = p4hir.read %[[VAL_8]] : <!b8i>
// CHECK:           %[[VAL_19:.*]] = p4hir.shl(%[[VAL_17]] : !i32i, %[[VAL_18]] : !b8i) : !i32i
// CHECK:           %[[VAL_20:.*]] = p4hir.variable ["s32i_shl_u8i", init] : <!i32i>
// CHECK:           p4hir.assign %[[VAL_19]], %[[VAL_20]] : <!i32i>
// CHECK:           %[[VAL_21:.*]] = p4hir.const #[[$ATTR_2]]
// CHECK:           %[[VAL_22:.*]] = p4hir.read %[[VAL_5]] : <!i32i>
// CHECK:           %[[VAL_23:.*]] = p4hir.shl(%[[VAL_22]] : !i32i, %[[VAL_21]] : !infint) : !i32i
// CHECK:           %[[VAL_24:.*]] = p4hir.variable ["s32i_shl_int", init] : <!i32i>
// CHECK:           p4hir.assign %[[VAL_23]], %[[VAL_24]] : <!i32i>
// CHECK:           %[[VAL_25:.*]] = p4hir.const ["int_shl_int"] #[[$ATTR_5]]
// CHECK:           %[[VAL_26:.*]] = p4hir.read %[[VAL_2]] : <!b32i>
// CHECK:           %[[VAL_27:.*]] = p4hir.read %[[VAL_8]] : <!b8i>
// CHECK:           %[[VAL_28:.*]] = p4hir.shr(%[[VAL_26]] : !b32i, %[[VAL_27]] : !b8i) : !b32i
// CHECK:           %[[VAL_29:.*]] = p4hir.variable ["u32i_shr_u8i", init] : <!b32i>
// CHECK:           p4hir.assign %[[VAL_28]], %[[VAL_29]] : <!b32i>
// CHECK:           %[[VAL_30:.*]] = p4hir.const #[[$ATTR_2]]
// CHECK:           %[[VAL_31:.*]] = p4hir.read %[[VAL_2]] : <!b32i>
// CHECK:           %[[VAL_32:.*]] = p4hir.shr(%[[VAL_31]] : !b32i, %[[VAL_30]] : !infint) : !b32i
// CHECK:           %[[VAL_33:.*]] = p4hir.variable ["u32i_shr_int", init] : <!b32i>
// CHECK:           p4hir.assign %[[VAL_32]], %[[VAL_33]] : <!b32i>
// CHECK:           %[[VAL_34:.*]] = p4hir.read %[[VAL_5]] : <!i32i>
// CHECK:           %[[VAL_35:.*]] = p4hir.read %[[VAL_8]] : <!b8i>
// CHECK:           %[[VAL_36:.*]] = p4hir.shr(%[[VAL_34]] : !i32i, %[[VAL_35]] : !b8i) : !i32i
// CHECK:           %[[VAL_37:.*]] = p4hir.variable ["s32i_shr_u8i", init] : <!i32i>
// CHECK:           p4hir.assign %[[VAL_36]], %[[VAL_37]] : <!i32i>
// CHECK:           %[[VAL_38:.*]] = p4hir.const #[[$ATTR_2]]
// CHECK:           %[[VAL_39:.*]] = p4hir.read %[[VAL_5]] : <!i32i>
// CHECK:           %[[VAL_40:.*]] = p4hir.shr(%[[VAL_39]] : !i32i, %[[VAL_38]] : !infint) : !i32i
// CHECK:           %[[VAL_41:.*]] = p4hir.variable ["s32i_shr_int", init] : <!i32i>
// CHECK:           p4hir.assign %[[VAL_40]], %[[VAL_41]] : <!i32i>
// CHECK:           %[[VAL_42:.*]] = p4hir.const ["int_shr_int"] #[[$ATTR_0]]
// CHECK:           p4hir.return
// CHECK:         }
