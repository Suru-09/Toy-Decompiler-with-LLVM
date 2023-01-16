source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [24 x i8] c"Two way conditional: %d\00"
@0 = external global i32

define i64 @_init() local_unnamed_addr {
dec_label_pc_1000:
  %rax.0.reg2mem = alloca i64, !insn.addr !0
  %0 = load i64, i64* inttoptr (i64 16360 to i64*), align 8, !insn.addr !1
  %1 = icmp eq i64 %0, 0, !insn.addr !2
  store i64 0, i64* %rax.0.reg2mem, !insn.addr !3
  br i1 %1, label %dec_label_pc_1016, label %dec_label_pc_1014, !insn.addr !3

dec_label_pc_1014:                                ; preds = %dec_label_pc_1000
  call void @__gmon_start__(), !insn.addr !4
  store i64 ptrtoint (i32* @0 to i64), i64* %rax.0.reg2mem, !insn.addr !4
  br label %dec_label_pc_1016, !insn.addr !4

dec_label_pc_1016:                                ; preds = %dec_label_pc_1014, %dec_label_pc_1000
  %rax.0.reload = load i64, i64* %rax.0.reg2mem
  ret i64 %rax.0.reload, !insn.addr !5
}

define void @function_1040(i64* %d) local_unnamed_addr {
dec_label_pc_1040:
  call void @__cxa_finalize(i64* %d), !insn.addr !6
  ret void, !insn.addr !6
}

define i32 @function_1050(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1050:
  %0 = call i32 (i8*, ...) @printf(i8* %format), !insn.addr !7
  ret i32 %0, !insn.addr !7
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1060:
  %stack_var_8 = alloca i64, align 8
  %0 = trunc i64 %arg6 to i32, !insn.addr !8
  %1 = bitcast i64* %stack_var_8 to i8**, !insn.addr !8
  %2 = inttoptr i64 %arg3 to void ()*, !insn.addr !8
  %3 = call i32 @__libc_start_main(i64 4508, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !8
  %4 = call i64 @__asm_hlt(), !insn.addr !9
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
  %0 = alloca i64
  %1 = load i64, i64* %0
  %2 = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !12
  %3 = icmp eq i8 %2, 0, !insn.addr !12
  %4 = icmp eq i1 %3, false, !insn.addr !13
  br i1 %4, label %dec_label_pc_1138, label %dec_label_pc_110d, !insn.addr !13

dec_label_pc_110d:                                ; preds = %dec_label_pc_1100
  %5 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !14
  %6 = icmp eq i64 %5, 0, !insn.addr !14
  br i1 %6, label %dec_label_pc_1127, label %dec_label_pc_111b, !insn.addr !15

dec_label_pc_111b:                                ; preds = %dec_label_pc_110d
  %7 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !16
  %8 = inttoptr i64 %7 to i64*, !insn.addr !17
  call void @__cxa_finalize(i64* %8), !insn.addr !17
  br label %dec_label_pc_1127, !insn.addr !17

dec_label_pc_1127:                                ; preds = %dec_label_pc_111b, %dec_label_pc_110d
  %9 = call i64 @deregister_tm_clones(), !insn.addr !18
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !19
  ret i64 %9, !insn.addr !20

dec_label_pc_1138:                                ; preds = %dec_label_pc_1100
  ret i64 %1, !insn.addr !21
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1140:
  %0 = call i64 @register_tm_clones(), !insn.addr !22
  ret i64 %0, !insn.addr !22
}

define i32 @two_way(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %rax.0.reg2mem = alloca i32, !insn.addr !23
  %0 = icmp sgt i32 %n, 4, !insn.addr !24
  br i1 %0, label %dec_label_pc_116e, label %dec_label_pc_115a, !insn.addr !24

dec_label_pc_115a:                                ; preds = %dec_label_pc_1149
  %1 = icmp eq i32 %n, 0, !insn.addr !25
  %2 = icmp slt i32 %n, 0, !insn.addr !25
  %3 = icmp eq i1 %2, false, !insn.addr !26
  %4 = icmp eq i1 %1, false, !insn.addr !26
  %5 = icmp eq i1 %3, %4, !insn.addr !26
  %. = select i1 %5, i32 3, i32 2
  store i32 %., i32* %rax.0.reg2mem, !insn.addr !27
  br label %dec_label_pc_119a, !insn.addr !27

dec_label_pc_116e:                                ; preds = %dec_label_pc_1149
  %6 = icmp eq i32 %n, 5, !insn.addr !28
  store i32 6, i32* %rax.0.reg2mem, !insn.addr !28
  br i1 %6, label %dec_label_pc_119a, label %dec_label_pc_1174, !insn.addr !28

dec_label_pc_1174:                                ; preds = %dec_label_pc_116e
  %7 = icmp slt i32 %n, 16, !insn.addr !29
  store i32 4, i32* %rax.0.reg2mem, !insn.addr !29
  br i1 %7, label %dec_label_pc_1181, label %dec_label_pc_119a, !insn.addr !29

dec_label_pc_1181:                                ; preds = %dec_label_pc_1174
  %8 = icmp slt i32 %n, 11, !insn.addr !30
  %.1 = select i1 %8, i32 6, i32 5
  store i32 %.1, i32* %rax.0.reg2mem, !insn.addr !31
  br label %dec_label_pc_119a, !insn.addr !31

dec_label_pc_119a:                                ; preds = %dec_label_pc_116e, %dec_label_pc_1181, %dec_label_pc_1174, %dec_label_pc_115a
  %rax.0.reload = load i32, i32* %rax.0.reg2mem
  ret i32 %rax.0.reload, !insn.addr !32

; uselistorder directives
  uselistorder i32* %rax.0.reg2mem, { 0, 2, 3, 1, 4 }
  uselistorder i32 6, { 1, 0 }
  uselistorder i1 false, { 2, 0, 1 }
  uselistorder i32 %n, { 1, 2, 0, 3, 4, 5 }
  uselistorder label %dec_label_pc_119a, { 1, 2, 0, 3 }
}

define i32 @main() local_unnamed_addr {
dec_label_pc_119c:
  %0 = call i32 @two_way(i32 15), !insn.addr !33
  %1 = zext i32 %0 to i64, !insn.addr !34
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @global_var_2004, i64 0, i64 0), i64 %1), !insn.addr !35
  ret i32 0, !insn.addr !36

; uselistorder directives
  uselistorder i64 0, { 2, 3, 5, 1, 0, 6, 4 }
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_11cc:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !37

; uselistorder directives
  uselistorder i32 1, { 1, 2, 0, 4, 3 }
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
!18 = !{i64 4391}
!19 = !{i64 4396}
!20 = !{i64 4404}
!21 = !{i64 4408}
!22 = !{i64 4420}
!23 = !{i64 4425}
!24 = !{i64 4440}
!25 = !{i64 4442}
!26 = !{i64 4446}
!27 = !{i64 4460}
!28 = !{i64 4466}
!29 = !{i64 4472}
!30 = !{i64 4485}
!31 = !{i64 4499}
!32 = !{i64 4507}
!33 = !{i64 4521}
!34 = !{i64 4526}
!35 = !{i64 4543}
!36 = !{i64 4554}
!37 = !{i64 4568}
