; ModuleID = '../testing_files/elfC/loops.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [4 x i8] c"%d\0A\00"
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
  %i2 = call i32 @__libc_start_main(i64 4742, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !7
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

define i32 @n_way_conditional_switch(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %i = icmp eq i32 %n, 5, !insn.addr !21
  br i1 %i, label %dec_label_pc_11a3, label %dec_label_pc_1161, !insn.addr !22

dec_label_pc_1161:                                ; preds = %dec_label_pc_1149
  %i1 = icmp sgt i32 %n, 5, !insn.addr !23
  br i1 %i1, label %dec_label_pc_11a3, label %dec_label_pc_1167, !insn.addr !23

dec_label_pc_1167:                                ; preds = %dec_label_pc_1161
  %i2 = icmp eq i32 %n, 3, !insn.addr !24
  br i1 %i2, label %dec_label_pc_11a3, label %dec_label_pc_116d, !insn.addr !25

dec_label_pc_116d:                                ; preds = %dec_label_pc_1167
  %i3 = icmp sgt i32 %n, 3, !insn.addr !26
  br i1 %i3, label %dec_label_pc_11a3, label %dec_label_pc_1173, !insn.addr !26

dec_label_pc_1173:                                ; preds = %dec_label_pc_116d
  %switch.selectcmp = icmp eq i32 %n, 2
  %switch.select = select i1 %switch.selectcmp, i32 18, i32 -1
  %switch.selectcmp1 = icmp eq i32 %n, 1
  %switch.select2 = select i1 %switch.selectcmp1, i32 20, i32 %switch.select
  br label %dec_label_pc_11a3

dec_label_pc_11a3:                                ; preds = %dec_label_pc_1161, %dec_label_pc_116d, %dec_label_pc_1173, %dec_label_pc_1149, %dec_label_pc_1167
  %rax.0.reg2mem.0 = phi i32 [ 5, %dec_label_pc_1149 ], [ -1, %dec_label_pc_1161 ], [ 16, %dec_label_pc_1167 ], [ -1, %dec_label_pc_116d ], [ %switch.select2, %dec_label_pc_1173 ]
  ret i32 %rax.0.reg2mem.0, !insn.addr !27
}

define i32 @for_loop(i32 %j) local_unnamed_addr {
dec_label_pc_11a5:
  %i = icmp sgt i32 %j, 0, !insn.addr !28
  br i1 %i, label %dec_label_pc_11c0.preheader, label %dec_label_pc_11ef, !insn.addr !28

dec_label_pc_11c0.preheader:                      ; preds = %dec_label_pc_11a5
  br label %dec_label_pc_11c0

dec_label_pc_11c0:                                ; preds = %dec_label_pc_11c0.preheader, %dec_label_pc_11c0
  %storemerge2.reg2mem.0 = phi i32 [ 0, %dec_label_pc_11c0.preheader ], [ %i2, %dec_label_pc_11c0 ]
  %stack_var_-28.01.reg2mem.0 = phi i32 [ 0, %dec_label_pc_11c0.preheader ], [ %i1, %dec_label_pc_11c0 ]
  %i1 = add i32 %stack_var_-28.01.reg2mem.0, 7, !insn.addr !29
  %i2 = add i32 %storemerge2.reg2mem.0, 2, !insn.addr !30
  %i3 = icmp slt i32 %i2, %j, !insn.addr !28
  br i1 %i3, label %dec_label_pc_11c0, label %dec_label_pc_11ef.loopexit, !insn.addr !28

dec_label_pc_11ef.loopexit:                       ; preds = %dec_label_pc_11c0
  br label %dec_label_pc_11ef

dec_label_pc_11ef:                                ; preds = %dec_label_pc_11ef.loopexit, %dec_label_pc_11a5
  %stack_var_-28.0.lcssa.reg2mem.0 = phi i32 [ %i1, %dec_label_pc_11ef.loopexit ], [ 0, %dec_label_pc_11a5 ]
  ret i32 %stack_var_-28.0.lcssa.reg2mem.0, !insn.addr !31
}

define i32 @while_pre_tested_loop(i32 %flag_2) local_unnamed_addr {
dec_label_pc_11f4:
  %i = icmp slt i32 %flag_2, 0, !insn.addr !32
  br i1 %i, label %dec_label_pc_123a, label %dec_label_pc_120f.preheader, !insn.addr !32

dec_label_pc_120f.preheader:                      ; preds = %dec_label_pc_11f4
  br label %dec_label_pc_120f

dec_label_pc_120f:                                ; preds = %dec_label_pc_120f.preheader, %dec_label_pc_120f
  %stack_var_-24.02.reg2mem.0 = phi i32 [ 0, %dec_label_pc_120f.preheader ], [ %i1, %dec_label_pc_120f ]
  %stack_var_-28.01.reg2mem.0 = phi i32 [ 0, %dec_label_pc_120f.preheader ], [ %i2, %dec_label_pc_120f ]
  %i1 = add i32 %stack_var_-24.02.reg2mem.0, 7, !insn.addr !33
  %i2 = add i32 %stack_var_-28.01.reg2mem.0, 1, !insn.addr !34
  %i3 = icmp sgt i32 %i2, %flag_2, !insn.addr !32
  br i1 %i3, label %dec_label_pc_123a.loopexit, label %dec_label_pc_120f, !insn.addr !32

dec_label_pc_123a.loopexit:                       ; preds = %dec_label_pc_120f
  br label %dec_label_pc_123a

dec_label_pc_123a:                                ; preds = %dec_label_pc_123a.loopexit, %dec_label_pc_11f4
  %stack_var_-24.0.lcssa.reg2mem.0 = phi i32 [ 0, %dec_label_pc_11f4 ], [ %i1, %dec_label_pc_123a.loopexit ]
  ret i32 %stack_var_-24.0.lcssa.reg2mem.0, !insn.addr !35
}

define i32 @while_post_tested_loop(i32 %flag) local_unnamed_addr {
dec_label_pc_123f:
  %i = icmp slt i32 %flag, 16, !insn.addr !36
  br label %dec_label_pc_1258, !insn.addr !37

dec_label_pc_1258:                                ; preds = %dec_label_pc_1258, %dec_label_pc_123f
  %stack_var_-24.0.reg2mem.0 = phi i32 [ 0, %dec_label_pc_123f ], [ %i1, %dec_label_pc_1258 ]
  %i1 = add i32 %stack_var_-24.0.reg2mem.0, 7, !insn.addr !38
  br i1 %i, label %dec_label_pc_1258, label %dec_label_pc_1281, !insn.addr !36

dec_label_pc_1281:                                ; preds = %dec_label_pc_1258
  ret i32 %i1, !insn.addr !39
}

define i32 @main() local_unnamed_addr {
dec_label_pc_1286:
  %i = call i32 @n_way_conditional_switch(i32 5), !insn.addr !40
  %i1 = zext i32 %i to i64, !insn.addr !41
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %i1), !insn.addr !42
  %i3 = call i32 @for_loop(i32 5), !insn.addr !43
  %i4 = zext i32 %i3 to i64, !insn.addr !44
  %i5 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %i4), !insn.addr !45
  %i6 = call i32 @while_pre_tested_loop(i32 5), !insn.addr !46
  %i7 = zext i32 %i6 to i64, !insn.addr !47
  %i8 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %i7), !insn.addr !48
  %i9 = call i32 @while_post_tested_loop(i32 5), !insn.addr !49
  %i10 = zext i32 %i9 to i64, !insn.addr !50
  %i11 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %i10), !insn.addr !51
  ret i32 0, !insn.addr !52
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1318:
  ret i64 undef, !insn.addr !53
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
!21 = !{i64 4443}
!22 = !{i64 4447}
!23 = !{i64 4453}
!24 = !{i64 4455}
!25 = !{i64 4459}
!26 = !{i64 4465}
!27 = !{i64 4516}
!28 = !{i64 4589}
!29 = !{i64 4572}
!30 = !{i64 4579}
!31 = !{i64 4595}
!32 = !{i64 4664}
!33 = !{i64 4651}
!34 = !{i64 4654}
!35 = !{i64 4670}
!36 = !{i64 4735}
!37 = !{i64 4689}
!38 = !{i64 4724}
!39 = !{i64 4741}
!40 = !{i64 4755}
!41 = !{i64 4760}
!42 = !{i64 4777}
!43 = !{i64 4787}
!44 = !{i64 4792}
!45 = !{i64 4809}
!46 = !{i64 4819}
!47 = !{i64 4824}
!48 = !{i64 4841}
!49 = !{i64 4851}
!50 = !{i64 4856}
!51 = !{i64 4873}
!52 = !{i64 4884}
!53 = !{i64 4900}
