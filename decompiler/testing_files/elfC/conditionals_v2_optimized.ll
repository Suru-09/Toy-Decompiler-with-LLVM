; ModuleID = '../testing_files/elfC/conditionals_v2.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [13 x i8] c"If else: %d\0A\00"
@global_var_2011 = constant [20 x i8] c"Nested if else: %d\0A\00"
@global_var_2025 = constant [17 x i8] c"Switch case: %d\0A\00"
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
  %i2 = call i32 @__libc_start_main(i64 4607, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !7
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

define i32 @if_else(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %i = icmp sgt i32 %n, 4, !insn.addr !21
  %. = select i1 %i, i32 3, i32 2
  ret i32 %., !insn.addr !22
}

define i32 @nested_if_else(i32 %j, i32 %i) local_unnamed_addr {
dec_label_pc_1168:
  %i1 = icmp sgt i32 %j, %i, !insn.addr !23
  %i2 = icmp slt i32 %j, 11
  %. = select i1 %i2, i32 5, i32 4
  %i3 = icmp slt i32 %i, 11
  %.1 = select i1 %i3, i32 7, i32 6
  %rax.0 = select i1 %i1, i32 %., i32 %.1
  ret i32 %rax.0, !insn.addr !24
}

define i32 @switch_case(i32 %n) local_unnamed_addr {
dec_label_pc_11a6:
  %i = icmp eq i32 %n, 6, !insn.addr !25
  br i1 %i, label %dec_label_pc_11fd, label %dec_label_pc_11b7, !insn.addr !26

dec_label_pc_11b7:                                ; preds = %dec_label_pc_11a6
  %i1 = icmp sgt i32 %n, 6, !insn.addr !27
  br i1 %i1, label %dec_label_pc_11fd, label %dec_label_pc_11bd, !insn.addr !27

dec_label_pc_11bd:                                ; preds = %dec_label_pc_11b7
  %i2 = icmp eq i32 %n, 3, !insn.addr !28
  br i1 %i2, label %dec_label_pc_11fd, label %dec_label_pc_11c3, !insn.addr !29

dec_label_pc_11c3:                                ; preds = %dec_label_pc_11bd
  %i3 = icmp sgt i32 %n, 3, !insn.addr !30
  br i1 %i3, label %dec_label_pc_11fd, label %dec_label_pc_11c9, !insn.addr !30

dec_label_pc_11c9:                                ; preds = %dec_label_pc_11c3
  %switch.selectcmp = icmp eq i32 %n, 2
  %switch.select = select i1 %switch.selectcmp, i32 15, i32 4
  %switch.selectcmp1 = icmp eq i32 %n, 1
  %switch.select2 = select i1 %switch.selectcmp1, i32 3, i32 %switch.select
  br label %dec_label_pc_11fd

dec_label_pc_11fd:                                ; preds = %dec_label_pc_11bd, %dec_label_pc_11b7, %dec_label_pc_11c3, %dec_label_pc_11c9, %dec_label_pc_11a6
  %rax.0.shrunk.reg2mem.0 = phi i32 [ 20, %dec_label_pc_11a6 ], [ 4, %dec_label_pc_11b7 ], [ 9, %dec_label_pc_11bd ], [ 4, %dec_label_pc_11c3 ], [ %switch.select2, %dec_label_pc_11c9 ]
  ret i32 %rax.0.shrunk.reg2mem.0, !insn.addr !31
}

define i32 @main() local_unnamed_addr {
dec_label_pc_11ff:
  %i = call i32 @if_else(i32 5), !insn.addr !32
  %i1 = zext i32 %i to i64, !insn.addr !33
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([13 x i8], [13 x i8]* @global_var_2004, i64 0, i64 0), i64 %i1), !insn.addr !34
  %i3 = call i32 @nested_if_else(i32 10, i32 5), !insn.addr !35
  %i4 = zext i32 %i3 to i64, !insn.addr !36
  %i5 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([20 x i8], [20 x i8]* @global_var_2011, i64 0, i64 0), i64 %i4), !insn.addr !37
  %i6 = call i32 @switch_case(i32 6), !insn.addr !38
  %i7 = zext i32 %i6 to i64, !insn.addr !39
  %i8 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([17 x i8], [17 x i8]* @global_var_2025, i64 0, i64 0), i64 %i7), !insn.addr !40
  ret i32 0, !insn.addr !41
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1274:
  ret i64 undef, !insn.addr !42
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
!22 = !{i64 4455}
!23 = !{i64 4476}
!24 = !{i64 4517}
!25 = !{i64 4529}
!26 = !{i64 4533}
!27 = !{i64 4539}
!28 = !{i64 4541}
!29 = !{i64 4545}
!30 = !{i64 4551}
!31 = !{i64 4606}
!32 = !{i64 4620}
!33 = !{i64 4625}
!34 = !{i64 4642}
!35 = !{i64 4657}
!36 = !{i64 4662}
!37 = !{i64 4679}
!38 = !{i64 4689}
!39 = !{i64 4694}
!40 = !{i64 4711}
!41 = !{i64 4722}
!42 = !{i64 4736}
