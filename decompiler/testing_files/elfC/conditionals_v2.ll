source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [13 x i8] c"If else: %d\0A\00"
@global_var_2011 = constant [20 x i8] c"Nested if else: %d\0A\00"
@global_var_2025 = constant [17 x i8] c"Switch case: %d\0A\00"
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
  %3 = call i32 @__libc_start_main(i64 4607, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !8
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

define i32 @if_else(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %0 = icmp sgt i32 %n, 4, !insn.addr !23
  %. = select i1 %0, i32 3, i32 2
  ret i32 %., !insn.addr !24
}

define i32 @nested_if_else(i32 %j, i32 %i) local_unnamed_addr {
dec_label_pc_1168:
  %0 = icmp sgt i32 %j, %i, !insn.addr !25
  %1 = icmp slt i32 %j, 11
  %. = select i1 %1, i32 5, i32 4
  %2 = icmp slt i32 %i, 11
  %.1 = select i1 %2, i32 7, i32 6
  %rax.0 = select i1 %0, i32 %., i32 %.1
  ret i32 %rax.0, !insn.addr !26
}

define i32 @switch_case(i32 %n) local_unnamed_addr {
dec_label_pc_11a6:
  %rax.0.shrunk.reg2mem = alloca i32, !insn.addr !27
  %0 = icmp eq i32 %n, 6, !insn.addr !28
  store i32 20, i32* %rax.0.shrunk.reg2mem, !insn.addr !29
  br i1 %0, label %dec_label_pc_11fd, label %dec_label_pc_11b7, !insn.addr !29

dec_label_pc_11b7:                                ; preds = %dec_label_pc_11a6
  %1 = icmp sgt i32 %n, 6, !insn.addr !30
  store i32 4, i32* %rax.0.shrunk.reg2mem, !insn.addr !30
  br i1 %1, label %dec_label_pc_11fd, label %dec_label_pc_11bd, !insn.addr !30

dec_label_pc_11bd:                                ; preds = %dec_label_pc_11b7
  %2 = icmp eq i32 %n, 3, !insn.addr !31
  store i32 9, i32* %rax.0.shrunk.reg2mem, !insn.addr !32
  br i1 %2, label %dec_label_pc_11fd, label %dec_label_pc_11c3, !insn.addr !32

dec_label_pc_11c3:                                ; preds = %dec_label_pc_11bd
  %3 = icmp sgt i32 %n, 3, !insn.addr !33
  store i32 4, i32* %rax.0.shrunk.reg2mem, !insn.addr !33
  br i1 %3, label %dec_label_pc_11fd, label %dec_label_pc_11c9, !insn.addr !33

dec_label_pc_11c9:                                ; preds = %dec_label_pc_11c3
  %switch.selectcmp = icmp eq i32 %n, 2
  %switch.select = select i1 %switch.selectcmp, i32 15, i32 4
  %switch.selectcmp1 = icmp eq i32 %n, 1
  %switch.select2 = select i1 %switch.selectcmp1, i32 3, i32 %switch.select
  store i32 %switch.select2, i32* %rax.0.shrunk.reg2mem
  br label %dec_label_pc_11fd

dec_label_pc_11fd:                                ; preds = %dec_label_pc_11bd, %dec_label_pc_11b7, %dec_label_pc_11c3, %dec_label_pc_11c9, %dec_label_pc_11a6
  %rax.0.shrunk.reload = load i32, i32* %rax.0.shrunk.reg2mem
  ret i32 %rax.0.shrunk.reload, !insn.addr !34

; uselistorder directives
  uselistorder i32* %rax.0.shrunk.reg2mem, { 0, 4, 3, 1, 2, 5 }
  uselistorder i32 3, { 0, 3, 2, 1 }
  uselistorder i32 4, { 2, 1, 0, 3, 4 }
  uselistorder label %dec_label_pc_11fd, { 3, 2, 0, 1, 4 }
}

define i32 @main() local_unnamed_addr {
dec_label_pc_11ff:
  %0 = call i32 @if_else(i32 5), !insn.addr !35
  %1 = zext i32 %0 to i64, !insn.addr !36
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @global_var_2004, i64 0, i64 0), i64 %1), !insn.addr !37
  %3 = call i32 @nested_if_else(i32 10, i32 5), !insn.addr !38
  %4 = zext i32 %3 to i64, !insn.addr !39
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @global_var_2011, i64 0, i64 0), i64 %4), !insn.addr !40
  %6 = call i32 @switch_case(i32 6), !insn.addr !41
  %7 = zext i32 %6 to i64, !insn.addr !42
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @global_var_2025, i64 0, i64 0), i64 %7), !insn.addr !43
  ret i32 0, !insn.addr !44

; uselistorder directives
  uselistorder i32 6, { 1, 3, 2, 0 }
  uselistorder i32 (i8*, ...)* @printf, { 0, 2, 1, 3 }
  uselistorder i64 0, { 2, 3, 4, 5, 6, 7, 9, 1, 0, 10, 8 }
  uselistorder i32 5, { 1, 2, 0 }
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1274:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !45

; uselistorder directives
  uselistorder i32 1, { 1, 4, 2, 0, 5, 3 }
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
!23 = !{i64 4440}
!24 = !{i64 4455}
!25 = !{i64 4476}
!26 = !{i64 4517}
!27 = !{i64 4518}
!28 = !{i64 4529}
!29 = !{i64 4533}
!30 = !{i64 4539}
!31 = !{i64 4541}
!32 = !{i64 4545}
!33 = !{i64 4551}
!34 = !{i64 4606}
!35 = !{i64 4620}
!36 = !{i64 4625}
!37 = !{i64 4642}
!38 = !{i64 4657}
!39 = !{i64 4662}
!40 = !{i64 4679}
!41 = !{i64 4689}
!42 = !{i64 4694}
!43 = !{i64 4711}
!44 = !{i64 4722}
!45 = !{i64 4736}
