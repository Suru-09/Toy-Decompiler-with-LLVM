; ModuleID = '../testing_files/elfC/conditionals.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [24 x i8] c"Two way conditional: %d\00"
@0 = external global i32

define i64 @_init() local_unnamed_addr {
dec_label_pc_1000:
  %rax.0.reg2mem = alloca i64, align 8, !insn.addr !0
  %i = load i64, i64* inttoptr (i64 16360 to i64*), align 8, !insn.addr !1
  %i1 = icmp eq i64 %i, 0, !insn.addr !2
  store i64 0, i64* %rax.0.reg2mem, align 8, !insn.addr !3
  br i1 %i1, label %dec_label_pc_1016, label %dec_label_pc_1014, !insn.addr !3

dec_label_pc_1014:                                ; preds = %dec_label_pc_1000
  call void @__gmon_start__(), !insn.addr !4
  store i64 ptrtoint (i32* @0 to i64), i64* %rax.0.reg2mem, align 8, !insn.addr !4
  br label %dec_label_pc_1016, !insn.addr !4

dec_label_pc_1016:                                ; preds = %dec_label_pc_1014, %dec_label_pc_1000
  %rax.0.reload = load i64, i64* %rax.0.reg2mem, align 8
  ret i64 %rax.0.reload, !insn.addr !5
}

define void @function_1040(i64* %d) local_unnamed_addr {
dec_label_pc_1040:
  call void @__cxa_finalize(i64* %d), !insn.addr !6
  ret void, !insn.addr !6
}

define i32 @function_1050(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1050:
  %i = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) %format), !insn.addr !7
  ret i32 %i, !insn.addr !7
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1060:
  %stack_var_8 = alloca i8*, align 8
  %i = trunc i64 %arg6 to i32, !insn.addr !8
  %i1 = inttoptr i64 %arg3 to void ()*, !insn.addr !8
  %i2 = call i32 @__libc_start_main(i64 4508, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !8
  %i3 = call i64 @__asm_hlt(), !insn.addr !9
  unreachable, !insn.addr !9
}

define i64 @deregister_tm_clones() local_unnamed_addr {
dec_label_pc_1090:
  ret i64 ptrtoint (i64* @global_var_4010 to i64), !insn.addr !10
}

define i64 @register_tm_clones() local_unnamed_addr {
dec_label_pc_10c0:
  ret i64 0, !insn.addr !11
}

define i64 @__do_global_dtors_aux() local_unnamed_addr {
dec_label_pc_1100:
  %i = alloca i64, align 8
  %i1 = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !12
  %.not = icmp eq i8 %i1, 0, !insn.addr !12
  br i1 %.not, label %dec_label_pc_110d, label %dec_label_pc_1138, !insn.addr !13

dec_label_pc_110d:                                ; preds = %dec_label_pc_1100
  %i2 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !14
  %i3 = icmp eq i64 %i2, 0, !insn.addr !14
  br i1 %i3, label %dec_label_pc_1127, label %dec_label_pc_111b, !insn.addr !15

dec_label_pc_111b:                                ; preds = %dec_label_pc_110d
  %i4 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !16
  %i5 = inttoptr i64 %i4 to i64*, !insn.addr !17
  call void @__cxa_finalize(i64* %i5), !insn.addr !17
  br label %dec_label_pc_1127, !insn.addr !17

common.ret:                                       ; preds = %dec_label_pc_1138, %dec_label_pc_1127
  %common.ret.op = phi i64 [ %i6, %dec_label_pc_1127 ], [ %i7, %dec_label_pc_1138 ]
  ret i64 %common.ret.op, !insn.addr !18

dec_label_pc_1127:                                ; preds = %dec_label_pc_111b, %dec_label_pc_110d
  %i6 = call i64 @deregister_tm_clones(), !insn.addr !19
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !20
  br label %common.ret

dec_label_pc_1138:                                ; preds = %dec_label_pc_1100
  %i7 = load i64, i64* %i, align 8
  br label %common.ret
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1140:
  %i = call i64 @register_tm_clones(), !insn.addr !21
  ret i64 %i, !insn.addr !21
}

define i32 @two_way(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %rax.0.reg2mem = alloca i32, align 4, !insn.addr !22
  %i = icmp sgt i32 %n, 4, !insn.addr !23
  br i1 %i, label %dec_label_pc_116e, label %dec_label_pc_115a, !insn.addr !23

dec_label_pc_115a:                                ; preds = %dec_label_pc_1149
  %i1 = icmp sgt i32 %n, 0
  %. = select i1 %i1, i32 3, i32 2
  store i32 %., i32* %rax.0.reg2mem, align 4, !insn.addr !24
  br label %dec_label_pc_119a, !insn.addr !24

dec_label_pc_116e:                                ; preds = %dec_label_pc_1149
  %i2 = icmp eq i32 %n, 5, !insn.addr !25
  store i32 6, i32* %rax.0.reg2mem, align 4, !insn.addr !25
  br i1 %i2, label %dec_label_pc_119a, label %dec_label_pc_1174, !insn.addr !25

dec_label_pc_1174:                                ; preds = %dec_label_pc_116e
  %i3 = icmp slt i32 %n, 16, !insn.addr !26
  store i32 4, i32* %rax.0.reg2mem, align 4, !insn.addr !26
  br i1 %i3, label %dec_label_pc_1181, label %dec_label_pc_119a, !insn.addr !26

dec_label_pc_1181:                                ; preds = %dec_label_pc_1174
  %i4 = icmp slt i32 %n, 11, !insn.addr !27
  %.1 = select i1 %i4, i32 6, i32 5
  store i32 %.1, i32* %rax.0.reg2mem, align 4, !insn.addr !28
  br label %dec_label_pc_119a, !insn.addr !28

dec_label_pc_119a:                                ; preds = %dec_label_pc_116e, %dec_label_pc_1181, %dec_label_pc_1174, %dec_label_pc_115a
  %rax.0.reload = load i32, i32* %rax.0.reg2mem, align 4
  ret i32 %rax.0.reload, !insn.addr !29
}

define i32 @main() local_unnamed_addr {
dec_label_pc_119c:
  %i = call i32 @two_way(i32 15), !insn.addr !30
  %i1 = zext i32 %i to i64, !insn.addr !31
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([24 x i8], [24 x i8]* @global_var_2004, i64 0, i64 0), i64 %i1), !insn.addr !32
  ret i32 0, !insn.addr !33
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_11cc:
  %i = alloca i64, align 8
  %i1 = load i64, i64* %i, align 8
  ret i64 %i1, !insn.addr !34
}

declare i32 @printf(i8*, ...) local_unnamed_addr

declare i32 @__libc_start_main(i64, i32, i8**, void ()*, void ()*, void ()*) local_unnamed_addr

declare void @__gmon_start__() local_unnamed_addr

declare void @__cxa_finalize(i64*) local_unnamed_addr

declare i64 @__asm_hlt() local_unnamed_addr

!0 = !{i64 4096}
!1 = !{i64 4104}
!2 = !{i64 4111}
!3 = !{i64 4114}
!4 = !{i64 4116}
!5 = !{i64 4122}
!6 = !{i64 4164}
!7 = !{i64 4180}
!8 = !{i64 4223}
!9 = !{i64 4229}
!10 = !{i64 4280}
!11 = !{i64 4344}
!12 = !{i64 4356}
!13 = !{i64 4363}
!14 = !{i64 4366}
!15 = !{i64 4377}
!16 = !{i64 4379}
!17 = !{i64 4386}
!18 = !{i64 4404}
!19 = !{i64 4391}
!20 = !{i64 4396}
!21 = !{i64 4420}
!22 = !{i64 4425}
!23 = !{i64 4440}
!24 = !{i64 4460}
!25 = !{i64 4466}
!26 = !{i64 4472}
!27 = !{i64 4485}
!28 = !{i64 4499}
!29 = !{i64 4507}
!30 = !{i64 4521}
!31 = !{i64 4526}
!32 = !{i64 4543}
!33 = !{i64 4554}
!34 = !{i64 4568}
