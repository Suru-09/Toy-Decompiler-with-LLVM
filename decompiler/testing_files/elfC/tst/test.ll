source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [20 x i8] c"Value of sum: <%d>\0A\00"
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
  %3 = call i32 @__libc_start_main(i64 4522, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !8
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

define i32 @calc_sum(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %stack_var_-20.2.lcssa.reg2mem = alloca i32, !insn.addr !23
  %stack_var_-20.25.reg2mem = alloca i32, !insn.addr !23
  %storemerge6.reg2mem = alloca i32, !insn.addr !23
  %stack_var_-20.1.lcssa.reg2mem = alloca i32, !insn.addr !23
  %stack_var_-20.12.reg2mem = alloca i32, !insn.addr !23
  %storemerge13.reg2mem = alloca i32, !insn.addr !23
  %0 = icmp sgt i32 %n, 0, !insn.addr !24
  store i32 0, i32* %stack_var_-20.2.lcssa.reg2mem, !insn.addr !24
  br i1 %0, label %dec_label_pc_1188.preheader.lr.ph, label %dec_label_pc_11a5, !insn.addr !24

dec_label_pc_1188.preheader.lr.ph:                ; preds = %dec_label_pc_1149
  %1 = ashr i32 %n, 1, !insn.addr !25
  %2 = zext i32 %1 to i64, !insn.addr !25
  %3 = icmp eq i32 %1, 0, !insn.addr !26
  store i32 0, i32* %storemerge6.reg2mem
  store i32 0, i32* %stack_var_-20.25.reg2mem
  br label %dec_label_pc_1188.preheader

dec_label_pc_116d:                                ; preds = %dec_label_pc_116d.lr.ph, %dec_label_pc_116d
  %stack_var_-20.12.reload = load i32, i32* %stack_var_-20.12.reg2mem
  %storemerge13.reload = load i32, i32* %storemerge13.reg2mem
  %4 = add i32 %storemerge13.reload, %11
  %5 = select i1 %10, i32 0, i32 %4
  %stack_var_-20.0 = add i32 %stack_var_-20.12.reload, %5
  %6 = add i32 %storemerge13.reload, 1, !insn.addr !27
  %7 = sext i32 %6 to i64, !insn.addr !26
  %8 = icmp slt i64 %7, %2, !insn.addr !26
  store i32 %6, i32* %storemerge13.reg2mem, !insn.addr !26
  store i32 %stack_var_-20.0, i32* %stack_var_-20.12.reg2mem, !insn.addr !26
  store i32 %stack_var_-20.0, i32* %stack_var_-20.1.lcssa.reg2mem, !insn.addr !26
  br i1 %8, label %dec_label_pc_116d, label %dec_label_pc_1199, !insn.addr !26

dec_label_pc_1199:                                ; preds = %dec_label_pc_116d, %dec_label_pc_1188.preheader
  %stack_var_-20.1.lcssa.reload = load i32, i32* %stack_var_-20.1.lcssa.reg2mem
  %9 = add nuw nsw i32 %storemerge6.reload, 1, !insn.addr !28
  %exitcond = icmp eq i32 %9, %n
  store i32 %9, i32* %storemerge6.reg2mem, !insn.addr !24
  store i32 %stack_var_-20.1.lcssa.reload, i32* %stack_var_-20.25.reg2mem, !insn.addr !24
  store i32 %stack_var_-20.1.lcssa.reload, i32* %stack_var_-20.2.lcssa.reg2mem, !insn.addr !24
  br i1 %exitcond, label %dec_label_pc_11a5, label %dec_label_pc_1188.preheader, !insn.addr !24

dec_label_pc_1188.preheader:                      ; preds = %dec_label_pc_1199, %dec_label_pc_1188.preheader.lr.ph
  %stack_var_-20.25.reload = load i32, i32* %stack_var_-20.25.reg2mem
  %storemerge6.reload = load i32, i32* %storemerge6.reg2mem
  store i32 %stack_var_-20.25.reload, i32* %stack_var_-20.1.lcssa.reg2mem, !insn.addr !26
  br i1 %3, label %dec_label_pc_1199, label %dec_label_pc_116d.lr.ph, !insn.addr !26

dec_label_pc_116d.lr.ph:                          ; preds = %dec_label_pc_1188.preheader
  %10 = icmp ult i32 %storemerge6.reload, 3, !insn.addr !29
  %11 = mul i32 %storemerge6.reload, 3
  store i32 0, i32* %storemerge13.reg2mem
  store i32 %stack_var_-20.25.reload, i32* %stack_var_-20.12.reg2mem
  br label %dec_label_pc_116d

dec_label_pc_11a5:                                ; preds = %dec_label_pc_1199, %dec_label_pc_1149
  %stack_var_-20.2.lcssa.reload = load i32, i32* %stack_var_-20.2.lcssa.reg2mem
  ret i32 %stack_var_-20.2.lcssa.reload, !insn.addr !30

; uselistorder directives
  uselistorder i32 %storemerge6.reload, { 1, 0, 2 }
  uselistorder i32* %storemerge13.reg2mem, { 2, 1, 0 }
  uselistorder i32* %stack_var_-20.12.reg2mem, { 2, 1, 0 }
  uselistorder i32* %stack_var_-20.1.lcssa.reg2mem, { 2, 0, 1 }
  uselistorder i32 %n, { 1, 0, 2 }
  uselistorder label %dec_label_pc_1199, { 1, 0 }
}

define i32 @main() local_unnamed_addr {
dec_label_pc_11aa:
  %0 = call i32 @calc_sum(i32 10), !insn.addr !31
  %1 = zext i32 %0 to i64, !insn.addr !32
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @global_var_2004, i64 0, i64 0), i64 %1), !insn.addr !33
  ret i32 0, !insn.addr !34

; uselistorder directives
  uselistorder i32 0, { 4, 3, 5, 1, 2, 6, 0, 7 }
  uselistorder i64 0, { 2, 3, 5, 1, 0, 6, 4 }
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_11dc:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !35

; uselistorder directives
  uselistorder i32 1, { 1, 11, 10, 12, 7, 6, 5, 4, 3, 2, 0, 9, 8 }
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
!24 = !{i64 4515}
!25 = !{i64 4498}
!26 = !{i64 4503}
!27 = !{i64 4484}
!28 = !{i64 4505}
!29 = !{i64 4465}
!30 = !{i64 4521}
!31 = !{i64 4535}
!32 = !{i64 4540}
!33 = !{i64 4557}
!34 = !{i64 4568}
!35 = !{i64 4584}
