; ModuleID = '../testing_files/elfC/loops.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [14 x i8] c"Found myself!\00"
@global_var_2012 = constant [4 x i8] c"%d\0A\00"
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

define void @function_1050(i64* %d) local_unnamed_addr {
dec_label_pc_1050:
  call void @__cxa_finalize(i64* %d), !insn.addr !6
  ret void, !insn.addr !6
}

define i32 @function_1060(i8* %s) local_unnamed_addr {
dec_label_pc_1060:
  %i = call i32 @puts(i8* noundef nonnull dereferenceable(1) %s), !insn.addr !7
  ret i32 %i, !insn.addr !7
}

define i32 @function_1070(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1070:
  %i = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) %format), !insn.addr !8
  ret i32 %i, !insn.addr !8
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1080:
  %stack_var_8 = alloca i8*, align 8
  %i = trunc i64 %arg6 to i32, !insn.addr !9
  %i1 = inttoptr i64 %arg3 to void ()*, !insn.addr !9
  %i2 = call i32 @__libc_start_main(i64 4793, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !9
  %i3 = call i64 @__asm_hlt(), !insn.addr !10
  unreachable, !insn.addr !10
}

define i64 @deregister_tm_clones() local_unnamed_addr {
dec_label_pc_10b0:
  ret i64 ptrtoint (i64* @global_var_4010 to i64), !insn.addr !11
}

define i64 @register_tm_clones() local_unnamed_addr {
dec_label_pc_10e0:
  ret i64 0, !insn.addr !12
}

define i64 @__do_global_dtors_aux() local_unnamed_addr {
dec_label_pc_1120:
  %i = alloca i64, align 8
  %i1 = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !13
  %.not = icmp eq i8 %i1, 0, !insn.addr !13
  br i1 %.not, label %dec_label_pc_112d, label %dec_label_pc_1158, !insn.addr !14

dec_label_pc_112d:                                ; preds = %dec_label_pc_1120
  %i2 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !15
  %i3 = icmp eq i64 %i2, 0, !insn.addr !15
  br i1 %i3, label %dec_label_pc_1147, label %dec_label_pc_113b, !insn.addr !16

dec_label_pc_113b:                                ; preds = %dec_label_pc_112d
  %i4 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !17
  %i5 = inttoptr i64 %i4 to i64*, !insn.addr !18
  call void @__cxa_finalize(i64* %i5), !insn.addr !18
  br label %dec_label_pc_1147, !insn.addr !18

common.ret:                                       ; preds = %dec_label_pc_1158, %dec_label_pc_1147
  %common.ret.op = phi i64 [ %i6, %dec_label_pc_1147 ], [ %i7, %dec_label_pc_1158 ]
  ret i64 %common.ret.op, !insn.addr !19

dec_label_pc_1147:                                ; preds = %dec_label_pc_113b, %dec_label_pc_112d
  %i6 = call i64 @deregister_tm_clones(), !insn.addr !20
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !21
  br label %common.ret

dec_label_pc_1158:                                ; preds = %dec_label_pc_1120
  %i7 = load i64, i64* %i, align 8
  br label %common.ret
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1160:
  %i = call i64 @register_tm_clones(), !insn.addr !22
  ret i64 %i, !insn.addr !22
}

define i32 @n_way_conditional_switch(i32 %n) local_unnamed_addr {
dec_label_pc_1169:
  %rax.0.reg2mem = alloca i32, align 4, !insn.addr !23
  %i = icmp eq i32 %n, 5, !insn.addr !24
  br i1 %i, label %dec_label_pc_11bd, label %dec_label_pc_1185, !insn.addr !25

dec_label_pc_1185:                                ; preds = %dec_label_pc_1169
  %i1 = icmp sgt i32 %n, 5, !insn.addr !26
  store i32 -1, i32* %rax.0.reg2mem, align 4, !insn.addr !26
  br i1 %i1, label %dec_label_pc_11d6, label %dec_label_pc_118b, !insn.addr !26

dec_label_pc_118b:                                ; preds = %dec_label_pc_1185
  %i2 = icmp eq i32 %n, 3, !insn.addr !27
  store i32 16, i32* %rax.0.reg2mem, align 4, !insn.addr !28
  br i1 %i2, label %dec_label_pc_11d6, label %dec_label_pc_1191, !insn.addr !28

dec_label_pc_1191:                                ; preds = %dec_label_pc_118b
  %i3 = icmp sgt i32 %n, 3, !insn.addr !29
  store i32 -1, i32* %rax.0.reg2mem, align 4, !insn.addr !29
  br i1 %i3, label %dec_label_pc_11d6, label %dec_label_pc_1197, !insn.addr !29

dec_label_pc_1197:                                ; preds = %dec_label_pc_1191
  %switch.selectcmp = icmp eq i32 %n, 2
  %switch.select = select i1 %switch.selectcmp, i32 18, i32 -1
  %switch.selectcmp1 = icmp eq i32 %n, 1
  %switch.select2 = select i1 %switch.selectcmp1, i32 20, i32 %switch.select
  store i32 %switch.select2, i32* %rax.0.reg2mem, align 4
  br label %dec_label_pc_11d6

dec_label_pc_11bd:                                ; preds = %dec_label_pc_1169
  %i4 = call i32 @puts(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([14 x i8], [14 x i8]* @global_var_2004, i64 0, i64 0)), !insn.addr !30
  store i32 5, i32* %rax.0.reg2mem, align 4, !insn.addr !31
  br label %dec_label_pc_11d6, !insn.addr !31

dec_label_pc_11d6:                                ; preds = %dec_label_pc_1185, %dec_label_pc_1191, %dec_label_pc_1197, %dec_label_pc_118b, %dec_label_pc_11bd
  %rax.0.reload = load i32, i32* %rax.0.reg2mem, align 4
  ret i32 %rax.0.reload, !insn.addr !32
}

define i32 @for_loop(i32 %j) local_unnamed_addr {
dec_label_pc_11d8:
  %stack_var_-28.0.lcssa.reg2mem = alloca i32, align 4, !insn.addr !33
  %stack_var_-28.01.reg2mem = alloca i32, align 4, !insn.addr !33
  %storemerge2.reg2mem = alloca i32, align 4, !insn.addr !33
  %i = icmp sgt i32 %j, 0, !insn.addr !34
  store i32 0, i32* %storemerge2.reg2mem, align 4, !insn.addr !34
  store i32 0, i32* %stack_var_-28.01.reg2mem, align 4, !insn.addr !34
  store i32 0, i32* %stack_var_-28.0.lcssa.reg2mem, align 4, !insn.addr !34
  br i1 %i, label %dec_label_pc_11f3.preheader, label %dec_label_pc_1222, !insn.addr !34

dec_label_pc_11f3.preheader:                      ; preds = %dec_label_pc_11d8
  br label %dec_label_pc_11f3

dec_label_pc_11f3:                                ; preds = %dec_label_pc_11f3.preheader, %dec_label_pc_11f3
  %stack_var_-28.01.reload = load i32, i32* %stack_var_-28.01.reg2mem, align 4
  %storemerge2.reload = load i32, i32* %storemerge2.reg2mem, align 4
  %i1 = add i32 %stack_var_-28.01.reload, 7, !insn.addr !35
  %i2 = add i32 %storemerge2.reload, 2, !insn.addr !36
  %i3 = icmp slt i32 %i2, %j, !insn.addr !34
  store i32 %i2, i32* %storemerge2.reg2mem, align 4, !insn.addr !34
  store i32 %i1, i32* %stack_var_-28.01.reg2mem, align 4, !insn.addr !34
  store i32 %i1, i32* %stack_var_-28.0.lcssa.reg2mem, align 4, !insn.addr !34
  br i1 %i3, label %dec_label_pc_11f3, label %dec_label_pc_1222.loopexit, !insn.addr !34

dec_label_pc_1222.loopexit:                       ; preds = %dec_label_pc_11f3
  br label %dec_label_pc_1222

dec_label_pc_1222:                                ; preds = %dec_label_pc_1222.loopexit, %dec_label_pc_11d8
  %stack_var_-28.0.lcssa.reload = load i32, i32* %stack_var_-28.0.lcssa.reg2mem, align 4
  ret i32 %stack_var_-28.0.lcssa.reload, !insn.addr !37
}

define i32 @while_pre_tested_loop(i32 %flag_2) local_unnamed_addr {
dec_label_pc_1227:
  %stack_var_-24.0.lcssa.reg2mem = alloca i32, align 4, !insn.addr !38
  %stack_var_-28.01.reg2mem = alloca i32, align 4, !insn.addr !38
  %stack_var_-24.02.reg2mem = alloca i32, align 4, !insn.addr !38
  %i = icmp slt i32 %flag_2, 0, !insn.addr !39
  store i32 0, i32* %stack_var_-24.02.reg2mem, align 4, !insn.addr !39
  store i32 0, i32* %stack_var_-28.01.reg2mem, align 4, !insn.addr !39
  store i32 0, i32* %stack_var_-24.0.lcssa.reg2mem, align 4, !insn.addr !39
  br i1 %i, label %dec_label_pc_126d, label %dec_label_pc_1242.preheader, !insn.addr !39

dec_label_pc_1242.preheader:                      ; preds = %dec_label_pc_1227
  br label %dec_label_pc_1242

dec_label_pc_1242:                                ; preds = %dec_label_pc_1242.preheader, %dec_label_pc_1242
  %stack_var_-28.01.reload = load i32, i32* %stack_var_-28.01.reg2mem, align 4
  %stack_var_-24.02.reload = load i32, i32* %stack_var_-24.02.reg2mem, align 4
  %i1 = add i32 %stack_var_-24.02.reload, 7, !insn.addr !40
  %i2 = add i32 %stack_var_-28.01.reload, 1, !insn.addr !41
  %i3 = icmp sgt i32 %i2, %flag_2, !insn.addr !39
  store i32 %i1, i32* %stack_var_-24.02.reg2mem, align 4, !insn.addr !39
  store i32 %i2, i32* %stack_var_-28.01.reg2mem, align 4, !insn.addr !39
  store i32 %i1, i32* %stack_var_-24.0.lcssa.reg2mem, align 4, !insn.addr !39
  br i1 %i3, label %dec_label_pc_126d.loopexit, label %dec_label_pc_1242, !insn.addr !39

dec_label_pc_126d.loopexit:                       ; preds = %dec_label_pc_1242
  br label %dec_label_pc_126d

dec_label_pc_126d:                                ; preds = %dec_label_pc_126d.loopexit, %dec_label_pc_1227
  %stack_var_-24.0.lcssa.reload = load i32, i32* %stack_var_-24.0.lcssa.reg2mem, align 4
  ret i32 %stack_var_-24.0.lcssa.reload, !insn.addr !42
}

define i32 @while_post_tested_loop(i32 %flag) local_unnamed_addr {
dec_label_pc_1272:
  %stack_var_-24.0.reg2mem = alloca i32, align 4, !insn.addr !43
  %i = icmp slt i32 %flag, 16, !insn.addr !44
  store i32 0, i32* %stack_var_-24.0.reg2mem, align 4, !insn.addr !45
  br label %dec_label_pc_128b, !insn.addr !45

dec_label_pc_128b:                                ; preds = %dec_label_pc_128b, %dec_label_pc_1272
  %stack_var_-24.0.reload = load i32, i32* %stack_var_-24.0.reg2mem, align 4
  %i1 = add i32 %stack_var_-24.0.reload, 7, !insn.addr !46
  store i32 %i1, i32* %stack_var_-24.0.reg2mem, align 4, !insn.addr !44
  br i1 %i, label %dec_label_pc_128b, label %dec_label_pc_12b4, !insn.addr !44

dec_label_pc_12b4:                                ; preds = %dec_label_pc_128b
  ret i32 %i1, !insn.addr !47
}

define i32 @main() local_unnamed_addr {
dec_label_pc_12b9:
  %i = call i32 @n_way_conditional_switch(i32 5), !insn.addr !48
  %i1 = zext i32 %i to i64, !insn.addr !49
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %i1), !insn.addr !50
  %i3 = call i32 @for_loop(i32 5), !insn.addr !51
  %i4 = zext i32 %i3 to i64, !insn.addr !52
  %i5 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %i4), !insn.addr !53
  %i6 = call i32 @while_pre_tested_loop(i32 5), !insn.addr !54
  %i7 = zext i32 %i6 to i64, !insn.addr !55
  %i8 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %i7), !insn.addr !56
  %i9 = call i32 @while_post_tested_loop(i32 5), !insn.addr !57
  %i10 = zext i32 %i9 to i64, !insn.addr !58
  %i11 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %i10), !insn.addr !59
  ret i32 0, !insn.addr !60
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1348:
  %i = alloca i64, align 8
  %i1 = load i64, i64* %i, align 8
  ret i64 %i1, !insn.addr !61
}

declare i32 @puts(i8*) local_unnamed_addr

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
!6 = !{i64 4180}
!7 = !{i64 4196}
!8 = !{i64 4212}
!9 = !{i64 4255}
!10 = !{i64 4261}
!11 = !{i64 4312}
!12 = !{i64 4376}
!13 = !{i64 4388}
!14 = !{i64 4395}
!15 = !{i64 4398}
!16 = !{i64 4409}
!17 = !{i64 4411}
!18 = !{i64 4418}
!19 = !{i64 4436}
!20 = !{i64 4423}
!21 = !{i64 4428}
!22 = !{i64 4452}
!23 = !{i64 4457}
!24 = !{i64 4479}
!25 = !{i64 4483}
!26 = !{i64 4489}
!27 = !{i64 4491}
!28 = !{i64 4495}
!29 = !{i64 4501}
!30 = !{i64 4551}
!31 = !{i64 4559}
!32 = !{i64 4567}
!33 = !{i64 4568}
!34 = !{i64 4640}
!35 = !{i64 4623}
!36 = !{i64 4630}
!37 = !{i64 4646}
!38 = !{i64 4647}
!39 = !{i64 4715}
!40 = !{i64 4702}
!41 = !{i64 4705}
!42 = !{i64 4721}
!43 = !{i64 4722}
!44 = !{i64 4786}
!45 = !{i64 4740}
!46 = !{i64 4775}
!47 = !{i64 4792}
!48 = !{i64 4806}
!49 = !{i64 4811}
!50 = !{i64 4828}
!51 = !{i64 4838}
!52 = !{i64 4843}
!53 = !{i64 4860}
!54 = !{i64 4870}
!55 = !{i64 4875}
!56 = !{i64 4892}
!57 = !{i64 4902}
!58 = !{i64 4907}
!59 = !{i64 4924}
!60 = !{i64 4935}
!61 = !{i64 4948}
