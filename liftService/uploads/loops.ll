source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [14 x i8] c"Found myself!\00"
@global_var_2012 = constant [4 x i8] c"%d\0A\00"
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

define void @function_1050(i64* %d) local_unnamed_addr {
dec_label_pc_1050:
  call void @__cxa_finalize(i64* %d), !insn.addr !6
  ret void, !insn.addr !6
}

define i32 @function_1060(i8* %s) local_unnamed_addr {
dec_label_pc_1060:
  %0 = call i32 @puts(i8* %s), !insn.addr !7
  ret i32 %0, !insn.addr !7
}

define i32 @function_1070(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1070:
  %0 = call i32 (i8*, ...) @printf(i8* %format), !insn.addr !8
  ret i32 %0, !insn.addr !8
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1080:
  %stack_var_8 = alloca i64, align 8
  %0 = trunc i64 %arg6 to i32, !insn.addr !9
  %1 = bitcast i64* %stack_var_8 to i8**, !insn.addr !9
  %2 = inttoptr i64 %arg3 to void ()*, !insn.addr !9
  %3 = call i32 @__libc_start_main(i64 4793, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !9
  %4 = call i64 @__asm_hlt(), !insn.addr !10
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
  %0 = alloca i64
  %1 = load i64, i64* %0
  %2 = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !13
  %3 = icmp eq i8 %2, 0, !insn.addr !13
  %4 = icmp eq i1 %3, false, !insn.addr !14
  br i1 %4, label %dec_label_pc_1158, label %dec_label_pc_112d, !insn.addr !14

dec_label_pc_112d:                                ; preds = %dec_label_pc_1120
  %5 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !15
  %6 = icmp eq i64 %5, 0, !insn.addr !15
  br i1 %6, label %dec_label_pc_1147, label %dec_label_pc_113b, !insn.addr !16

dec_label_pc_113b:                                ; preds = %dec_label_pc_112d
  %7 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !17
  %8 = inttoptr i64 %7 to i64*, !insn.addr !18
  call void @__cxa_finalize(i64* %8), !insn.addr !18
  br label %dec_label_pc_1147, !insn.addr !18

dec_label_pc_1147:                                ; preds = %dec_label_pc_113b, %dec_label_pc_112d
  %9 = call i64 @deregister_tm_clones(), !insn.addr !19
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !20
  ret i64 %9, !insn.addr !21

dec_label_pc_1158:                                ; preds = %dec_label_pc_1120
  ret i64 %1, !insn.addr !22
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1160:
  %0 = call i64 @register_tm_clones(), !insn.addr !23
  ret i64 %0, !insn.addr !23
}

define i32 @n_way_conditional_switch(i32 %n) local_unnamed_addr {
dec_label_pc_1169:
  %rax.0.reg2mem = alloca i32, !insn.addr !24
  %0 = icmp eq i32 %n, 5, !insn.addr !25
  br i1 %0, label %dec_label_pc_11bd, label %dec_label_pc_1185, !insn.addr !26

dec_label_pc_1185:                                ; preds = %dec_label_pc_1169
  %1 = icmp sgt i32 %n, 5, !insn.addr !27
  store i32 -1, i32* %rax.0.reg2mem, !insn.addr !27
  br i1 %1, label %dec_label_pc_11d6, label %dec_label_pc_118b, !insn.addr !27

dec_label_pc_118b:                                ; preds = %dec_label_pc_1185
  %2 = icmp eq i32 %n, 3, !insn.addr !28
  store i32 16, i32* %rax.0.reg2mem, !insn.addr !29
  br i1 %2, label %dec_label_pc_11d6, label %dec_label_pc_1191, !insn.addr !29

dec_label_pc_1191:                                ; preds = %dec_label_pc_118b
  %3 = icmp sgt i32 %n, 3, !insn.addr !30
  store i32 -1, i32* %rax.0.reg2mem, !insn.addr !30
  br i1 %3, label %dec_label_pc_11d6, label %dec_label_pc_1197, !insn.addr !30

dec_label_pc_1197:                                ; preds = %dec_label_pc_1191
  %switch.selectcmp = icmp eq i32 %n, 2
  %switch.select = select i1 %switch.selectcmp, i32 18, i32 -1
  %switch.selectcmp1 = icmp eq i32 %n, 1
  %switch.select2 = select i1 %switch.selectcmp1, i32 20, i32 %switch.select
  store i32 %switch.select2, i32* %rax.0.reg2mem
  br label %dec_label_pc_11d6

dec_label_pc_11bd:                                ; preds = %dec_label_pc_1169
  %4 = call i32 @puts(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @global_var_2004, i64 0, i64 0)), !insn.addr !31
  store i32 5, i32* %rax.0.reg2mem, !insn.addr !32
  br label %dec_label_pc_11d6, !insn.addr !32

dec_label_pc_11d6:                                ; preds = %dec_label_pc_1185, %dec_label_pc_1191, %dec_label_pc_1197, %dec_label_pc_118b, %dec_label_pc_11bd
  %rax.0.reload = load i32, i32* %rax.0.reg2mem
  ret i32 %rax.0.reload, !insn.addr !33

; uselistorder directives
  uselistorder i32* %rax.0.reg2mem, { 0, 5, 3, 2, 4, 1 }
  uselistorder i32 3, { 1, 0 }
  uselistorder i32 -1, { 2, 1, 0 }
  uselistorder i32 %n, { 0, 1, 4, 3, 2, 5 }
  uselistorder label %dec_label_pc_11d6, { 4, 2, 1, 3, 0 }
}

define i32 @for_loop(i32 %j) local_unnamed_addr {
dec_label_pc_11d8:
  %stack_var_-28.0.lcssa.reg2mem = alloca i32, !insn.addr !34
  %stack_var_-28.01.reg2mem = alloca i32, !insn.addr !34
  %storemerge2.reg2mem = alloca i32, !insn.addr !34
  %0 = icmp sgt i32 %j, 0, !insn.addr !35
  store i32 0, i32* %storemerge2.reg2mem, !insn.addr !35
  store i32 0, i32* %stack_var_-28.01.reg2mem, !insn.addr !35
  store i32 0, i32* %stack_var_-28.0.lcssa.reg2mem, !insn.addr !35
  br i1 %0, label %dec_label_pc_11f3, label %dec_label_pc_1222, !insn.addr !35

dec_label_pc_11f3:                                ; preds = %dec_label_pc_11d8, %dec_label_pc_11f3
  %stack_var_-28.01.reload = load i32, i32* %stack_var_-28.01.reg2mem
  %storemerge2.reload = load i32, i32* %storemerge2.reg2mem
  %1 = add i32 %stack_var_-28.01.reload, 7, !insn.addr !36
  %2 = add i32 %storemerge2.reload, 2, !insn.addr !37
  %3 = icmp slt i32 %2, %j, !insn.addr !35
  store i32 %2, i32* %storemerge2.reg2mem, !insn.addr !35
  store i32 %1, i32* %stack_var_-28.01.reg2mem, !insn.addr !35
  store i32 %1, i32* %stack_var_-28.0.lcssa.reg2mem, !insn.addr !35
  br i1 %3, label %dec_label_pc_11f3, label %dec_label_pc_1222, !insn.addr !35

dec_label_pc_1222:                                ; preds = %dec_label_pc_11f3, %dec_label_pc_11d8
  %stack_var_-28.0.lcssa.reload = load i32, i32* %stack_var_-28.0.lcssa.reg2mem
  ret i32 %stack_var_-28.0.lcssa.reload, !insn.addr !38

; uselistorder directives
  uselistorder i32* %storemerge2.reg2mem, { 2, 0, 1 }
  uselistorder i32* %stack_var_-28.01.reg2mem, { 2, 0, 1 }
  uselistorder i32 2, { 1, 0 }
  uselistorder i32 %j, { 1, 0 }
  uselistorder label %dec_label_pc_11f3, { 1, 0 }
}

define i32 @while_pre_tested_loop(i32 %flag_2) local_unnamed_addr {
dec_label_pc_1227:
  %stack_var_-24.0.lcssa.reg2mem = alloca i32, !insn.addr !39
  %stack_var_-28.01.reg2mem = alloca i32, !insn.addr !39
  %stack_var_-24.02.reg2mem = alloca i32, !insn.addr !39
  %0 = icmp slt i32 %flag_2, 0, !insn.addr !40
  store i32 0, i32* %stack_var_-24.02.reg2mem, !insn.addr !40
  store i32 0, i32* %stack_var_-28.01.reg2mem, !insn.addr !40
  store i32 0, i32* %stack_var_-24.0.lcssa.reg2mem, !insn.addr !40
  br i1 %0, label %dec_label_pc_126d, label %dec_label_pc_1242, !insn.addr !40

dec_label_pc_1242:                                ; preds = %dec_label_pc_1227, %dec_label_pc_1242
  %stack_var_-28.01.reload = load i32, i32* %stack_var_-28.01.reg2mem
  %stack_var_-24.02.reload = load i32, i32* %stack_var_-24.02.reg2mem
  %1 = add i32 %stack_var_-24.02.reload, 7, !insn.addr !41
  %2 = add i32 %stack_var_-28.01.reload, 1, !insn.addr !42
  %3 = icmp sgt i32 %2, %flag_2, !insn.addr !40
  store i32 %1, i32* %stack_var_-24.02.reg2mem, !insn.addr !40
  store i32 %2, i32* %stack_var_-28.01.reg2mem, !insn.addr !40
  store i32 %1, i32* %stack_var_-24.0.lcssa.reg2mem, !insn.addr !40
  br i1 %3, label %dec_label_pc_126d, label %dec_label_pc_1242, !insn.addr !40

dec_label_pc_126d:                                ; preds = %dec_label_pc_1242, %dec_label_pc_1227
  %stack_var_-24.0.lcssa.reload = load i32, i32* %stack_var_-24.0.lcssa.reg2mem
  ret i32 %stack_var_-24.0.lcssa.reload, !insn.addr !43

; uselistorder directives
  uselistorder i32* %stack_var_-24.02.reg2mem, { 2, 0, 1 }
  uselistorder i32* %stack_var_-28.01.reg2mem, { 2, 0, 1 }
  uselistorder i32 %flag_2, { 1, 0 }
  uselistorder label %dec_label_pc_1242, { 1, 0 }
}

define i32 @while_post_tested_loop(i32 %flag) local_unnamed_addr {
dec_label_pc_1272:
  %stack_var_-24.0.reg2mem = alloca i32, !insn.addr !44
  %0 = icmp slt i32 %flag, 16, !insn.addr !45
  store i32 0, i32* %stack_var_-24.0.reg2mem, !insn.addr !46
  br label %dec_label_pc_128b, !insn.addr !46

dec_label_pc_128b:                                ; preds = %dec_label_pc_128b, %dec_label_pc_1272
  %stack_var_-24.0.reload = load i32, i32* %stack_var_-24.0.reg2mem
  %1 = add i32 %stack_var_-24.0.reload, 7, !insn.addr !47
  store i32 %1, i32* %stack_var_-24.0.reg2mem, !insn.addr !45
  br i1 %0, label %dec_label_pc_128b, label %dec_label_pc_12b4, !insn.addr !45

dec_label_pc_12b4:                                ; preds = %dec_label_pc_128b
  ret i32 %1, !insn.addr !48

; uselistorder directives
  uselistorder i32 %1, { 1, 0 }
  uselistorder i32* %stack_var_-24.0.reg2mem, { 1, 0, 2 }
  uselistorder i32 16, { 1, 0 }
}

define i32 @main() local_unnamed_addr {
dec_label_pc_12b9:
  %0 = call i32 @n_way_conditional_switch(i32 5), !insn.addr !49
  %1 = zext i32 %0 to i64, !insn.addr !50
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %1), !insn.addr !51
  %3 = call i32 @for_loop(i32 5), !insn.addr !52
  %4 = zext i32 %3 to i64, !insn.addr !53
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %4), !insn.addr !54
  %6 = call i32 @while_pre_tested_loop(i32 5), !insn.addr !55
  %7 = zext i32 %6 to i64, !insn.addr !56
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %7), !insn.addr !57
  %9 = call i32 @while_post_tested_loop(i32 5), !insn.addr !58
  %10 = zext i32 %9 to i64, !insn.addr !59
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2012, i64 0, i64 0), i64 %10), !insn.addr !60
  ret i32 0, !insn.addr !61

; uselistorder directives
  uselistorder i32 0, { 7, 0, 1, 2, 3, 8, 4, 5, 6, 9 }
  uselistorder i32 (i8*, ...)* @printf, { 0, 1, 3, 2, 4 }
  uselistorder i64 0, { 2, 3, 4, 5, 7, 1, 0, 8, 6 }
  uselistorder i32 5, { 1, 2, 3, 4, 0, 6, 5 }
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1348:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !62

; uselistorder directives
  uselistorder i32 1, { 1, 2, 13, 5, 4, 3, 8, 7, 6, 11, 9, 0, 12, 10 }
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
!19 = !{i64 4423}
!20 = !{i64 4428}
!21 = !{i64 4436}
!22 = !{i64 4440}
!23 = !{i64 4452}
!24 = !{i64 4457}
!25 = !{i64 4479}
!26 = !{i64 4483}
!27 = !{i64 4489}
!28 = !{i64 4491}
!29 = !{i64 4495}
!30 = !{i64 4501}
!31 = !{i64 4551}
!32 = !{i64 4559}
!33 = !{i64 4567}
!34 = !{i64 4568}
!35 = !{i64 4640}
!36 = !{i64 4623}
!37 = !{i64 4630}
!38 = !{i64 4646}
!39 = !{i64 4647}
!40 = !{i64 4715}
!41 = !{i64 4702}
!42 = !{i64 4705}
!43 = !{i64 4721}
!44 = !{i64 4722}
!45 = !{i64 4786}
!46 = !{i64 4740}
!47 = !{i64 4775}
!48 = !{i64 4792}
!49 = !{i64 4806}
!50 = !{i64 4811}
!51 = !{i64 4828}
!52 = !{i64 4838}
!53 = !{i64 4843}
!54 = !{i64 4860}
!55 = !{i64 4870}
!56 = !{i64 4875}
!57 = !{i64 4892}
!58 = !{i64 4902}
!59 = !{i64 4907}
!60 = !{i64 4924}
!61 = !{i64 4935}
!62 = !{i64 4948}
