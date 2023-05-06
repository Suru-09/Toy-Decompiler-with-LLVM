; ModuleID = '../testing_files/elfC/conditionals.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [24 x i8] c"Two way conditional: %d\00"
@0 = external global i32

define i64 @_init() local_unnamed_addr {
dec_label_pc_1000:
  %i = load i64, i64* inttoptr (i64 16360 to i64*), align 8, !insn.addr !0
  %i1 = icmp eq i64 %i, 0, !insn.addr !1
  br i1 %i1, label %dec_label_pc_1016, label %dec_label_pc_1014, !insn.addr !2

dec_label_pc_1014:                                ; preds = %dec_label_pc_1000
  call void @__gmon_start__(), !insn.addr !3
  br label %dec_label_pc_1016, !insn.addr !3

dec_label_pc_1016:                                ; preds = %dec_label_pc_1014, %dec_label_pc_1000
  %rax.0.reg2mem.0 = phi i64 [ 0, %dec_label_pc_1000 ], [ ptrtoint (i32* @0 to i64), %dec_label_pc_1014 ]
  ret i64 %rax.0.reg2mem.0, !insn.addr !4
}

define void @function_1040(i64* %d) local_unnamed_addr {
dec_label_pc_1040:
  call void @__cxa_finalize(i64* %d), !insn.addr !5
  ret void, !insn.addr !5
}

define i32 @function_1050(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1050:
  %i = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) %format), !insn.addr !6
  ret i32 %i, !insn.addr !6
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1060:
  %stack_var_8 = alloca i8*, align 8
  %i = trunc i64 %arg6 to i32, !insn.addr !7
  %i1 = inttoptr i64 %arg3 to void ()*, !insn.addr !7
  %i2 = call i32 @__libc_start_main(i64 4508, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !7
  %i3 = call i64 @__asm_hlt(), !insn.addr !8
  unreachable, !insn.addr !8
}

define i64 @deregister_tm_clones() local_unnamed_addr {
dec_label_pc_1090:
  ret i64 ptrtoint (i64* @global_var_4010 to i64), !insn.addr !9
}

define i64 @register_tm_clones() local_unnamed_addr {
dec_label_pc_10c0:
  ret i64 0, !insn.addr !10
}

define i64 @__do_global_dtors_aux() local_unnamed_addr {
dec_label_pc_1100:
  %i1 = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !11
  %.not = icmp eq i8 %i1, 0, !insn.addr !11
  br i1 %.not, label %dec_label_pc_110d, label %dec_label_pc_1138, !insn.addr !12

dec_label_pc_110d:                                ; preds = %dec_label_pc_1100
  %i2 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !13
  %i3 = icmp eq i64 %i2, 0, !insn.addr !13
  br i1 %i3, label %dec_label_pc_1127, label %dec_label_pc_111b, !insn.addr !14

dec_label_pc_111b:                                ; preds = %dec_label_pc_110d
  %i4 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !15
  %i5 = inttoptr i64 %i4 to i64*, !insn.addr !16
  call void @__cxa_finalize(i64* %i5), !insn.addr !16
  br label %dec_label_pc_1127, !insn.addr !16

common.ret:                                       ; preds = %dec_label_pc_1138, %dec_label_pc_1127
  %common.ret.op = phi i64 [ %i6, %dec_label_pc_1127 ], [ undef, %dec_label_pc_1138 ]
  ret i64 %common.ret.op, !insn.addr !17

dec_label_pc_1127:                                ; preds = %dec_label_pc_111b, %dec_label_pc_110d
  %i6 = call i64 @deregister_tm_clones(), !insn.addr !18
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !19
  br label %common.ret

dec_label_pc_1138:                                ; preds = %dec_label_pc_1100
  br label %common.ret
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1140:
  %i = call i64 @register_tm_clones(), !insn.addr !20
  ret i64 %i, !insn.addr !20
}

define i32 @two_way(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %i = icmp sgt i32 %n, 4, !insn.addr !21
  br i1 %i, label %dec_label_pc_116e, label %dec_label_pc_115a, !insn.addr !21

dec_label_pc_115a:                                ; preds = %dec_label_pc_1149
  %i1 = icmp sgt i32 %n, 0
  %. = select i1 %i1, i32 3, i32 2
  br label %dec_label_pc_119a, !insn.addr !22

dec_label_pc_116e:                                ; preds = %dec_label_pc_1149
  %i2 = icmp eq i32 %n, 5, !insn.addr !23
  br i1 %i2, label %dec_label_pc_119a, label %dec_label_pc_1174, !insn.addr !23

dec_label_pc_1174:                                ; preds = %dec_label_pc_116e
  %i3 = icmp slt i32 %n, 16, !insn.addr !24
  br i1 %i3, label %dec_label_pc_1181, label %dec_label_pc_119a, !insn.addr !24

dec_label_pc_1181:                                ; preds = %dec_label_pc_1174
  %i4 = icmp slt i32 %n, 11, !insn.addr !25
  %.1 = select i1 %i4, i32 6, i32 5
  br label %dec_label_pc_119a, !insn.addr !26

dec_label_pc_119a:                                ; preds = %dec_label_pc_116e, %dec_label_pc_1181, %dec_label_pc_1174, %dec_label_pc_115a
  %rax.0.reg2mem.0 = phi i32 [ 6, %dec_label_pc_116e ], [ %.1, %dec_label_pc_1181 ], [ 4, %dec_label_pc_1174 ], [ %., %dec_label_pc_115a ]
  ret i32 %rax.0.reg2mem.0, !insn.addr !27
}

define i32 @main() local_unnamed_addr {
dec_label_pc_119c:
  %i = call i32 @two_way(i32 15), !insn.addr !28
  %i1 = zext i32 %i to i64, !insn.addr !29
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([24 x i8], [24 x i8]* @global_var_2004, i64 0, i64 0), i64 %i1), !insn.addr !30
  ret i32 0, !insn.addr !31
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_11cc:
  ret i64 undef, !insn.addr !32
}

declare i32 @printf(i8*, ...) local_unnamed_addr

declare i32 @__libc_start_main(i64, i32, i8**, void ()*, void ()*, void ()*) local_unnamed_addr

declare void @__gmon_start__() local_unnamed_addr

declare void @__cxa_finalize(i64*) local_unnamed_addr

declare i64 @__asm_hlt() local_unnamed_addr

!0 = !{i64 4104}
!1 = !{i64 4111}
!2 = !{i64 4114}
!3 = !{i64 4116}
!4 = !{i64 4122}
!5 = !{i64 4164}
!6 = !{i64 4180}
!7 = !{i64 4223}
!8 = !{i64 4229}
!9 = !{i64 4280}
!10 = !{i64 4344}
!11 = !{i64 4356}
!12 = !{i64 4363}
!13 = !{i64 4366}
!14 = !{i64 4377}
!15 = !{i64 4379}
!16 = !{i64 4386}
!17 = !{i64 4404}
!18 = !{i64 4391}
!19 = !{i64 4396}
!20 = !{i64 4420}
!21 = !{i64 4440}
!22 = !{i64 4460}
!23 = !{i64 4466}
!24 = !{i64 4472}
!25 = !{i64 4485}
!26 = !{i64 4499}
!27 = !{i64 4507}
!28 = !{i64 4521}
!29 = !{i64 4526}
!30 = !{i64 4543}
!31 = !{i64 4554}
!32 = !{i64 4568}
