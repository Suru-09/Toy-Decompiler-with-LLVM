source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [4 x i8] c"%d\0A\00"
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
  %3 = call i32 @__libc_start_main(i64 4742, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !8
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

define i32 @n_way_conditional_switch(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %rax.0.reg2mem = alloca i32, !insn.addr !23
  %0 = icmp eq i32 %n, 5, !insn.addr !24
  store i32 5, i32* %rax.0.reg2mem, !insn.addr !25
  br i1 %0, label %dec_label_pc_11a3, label %dec_label_pc_1161, !insn.addr !25

dec_label_pc_1161:                                ; preds = %dec_label_pc_1149
  %1 = icmp sgt i32 %n, 5, !insn.addr !26
  store i32 -1, i32* %rax.0.reg2mem, !insn.addr !26
  br i1 %1, label %dec_label_pc_11a3, label %dec_label_pc_1167, !insn.addr !26

dec_label_pc_1167:                                ; preds = %dec_label_pc_1161
  %2 = icmp eq i32 %n, 3, !insn.addr !27
  store i32 16, i32* %rax.0.reg2mem, !insn.addr !28
  br i1 %2, label %dec_label_pc_11a3, label %dec_label_pc_116d, !insn.addr !28

dec_label_pc_116d:                                ; preds = %dec_label_pc_1167
  %3 = icmp sgt i32 %n, 3, !insn.addr !29
  store i32 -1, i32* %rax.0.reg2mem, !insn.addr !29
  br i1 %3, label %dec_label_pc_11a3, label %dec_label_pc_1173, !insn.addr !29

dec_label_pc_1173:                                ; preds = %dec_label_pc_116d
  %switch.selectcmp = icmp eq i32 %n, 2
  %switch.select = select i1 %switch.selectcmp, i32 18, i32 -1
  %switch.selectcmp1 = icmp eq i32 %n, 1
  %switch.select2 = select i1 %switch.selectcmp1, i32 20, i32 %switch.select
  store i32 %switch.select2, i32* %rax.0.reg2mem
  br label %dec_label_pc_11a3

dec_label_pc_11a3:                                ; preds = %dec_label_pc_1161, %dec_label_pc_116d, %dec_label_pc_1173, %dec_label_pc_1149, %dec_label_pc_1167
  %rax.0.reload = load i32, i32* %rax.0.reg2mem
  ret i32 %rax.0.reload, !insn.addr !30

; uselistorder directives
  uselistorder i32* %rax.0.reg2mem, { 0, 3, 2, 5, 1, 4 }
  uselistorder i32 3, { 1, 0 }
  uselistorder i32 -1, { 2, 1, 0 }
  uselistorder i32 %n, { 0, 1, 4, 3, 2, 5 }
  uselistorder label %dec_label_pc_11a3, { 2, 1, 4, 0, 3 }
}

define i32 @for_loop(i32 %j) local_unnamed_addr {
dec_label_pc_11a5:
  %stack_var_-28.0.lcssa.reg2mem = alloca i32, !insn.addr !31
  %stack_var_-28.01.reg2mem = alloca i32, !insn.addr !31
  %storemerge2.reg2mem = alloca i32, !insn.addr !31
  %0 = icmp sgt i32 %j, 0, !insn.addr !32
  store i32 0, i32* %storemerge2.reg2mem, !insn.addr !32
  store i32 0, i32* %stack_var_-28.01.reg2mem, !insn.addr !32
  store i32 0, i32* %stack_var_-28.0.lcssa.reg2mem, !insn.addr !32
  br i1 %0, label %dec_label_pc_11c0, label %dec_label_pc_11ef, !insn.addr !32

dec_label_pc_11c0:                                ; preds = %dec_label_pc_11a5, %dec_label_pc_11c0
  %stack_var_-28.01.reload = load i32, i32* %stack_var_-28.01.reg2mem
  %storemerge2.reload = load i32, i32* %storemerge2.reg2mem
  %1 = add i32 %stack_var_-28.01.reload, 7, !insn.addr !33
  %2 = add i32 %storemerge2.reload, 2, !insn.addr !34
  %3 = icmp slt i32 %2, %j, !insn.addr !32
  store i32 %2, i32* %storemerge2.reg2mem, !insn.addr !32
  store i32 %1, i32* %stack_var_-28.01.reg2mem, !insn.addr !32
  store i32 %1, i32* %stack_var_-28.0.lcssa.reg2mem, !insn.addr !32
  br i1 %3, label %dec_label_pc_11c0, label %dec_label_pc_11ef, !insn.addr !32

dec_label_pc_11ef:                                ; preds = %dec_label_pc_11c0, %dec_label_pc_11a5
  %stack_var_-28.0.lcssa.reload = load i32, i32* %stack_var_-28.0.lcssa.reg2mem
  ret i32 %stack_var_-28.0.lcssa.reload, !insn.addr !35

; uselistorder directives
  uselistorder i32* %storemerge2.reg2mem, { 2, 0, 1 }
  uselistorder i32* %stack_var_-28.01.reg2mem, { 2, 0, 1 }
  uselistorder i32 2, { 1, 0 }
  uselistorder i32 %j, { 1, 0 }
  uselistorder label %dec_label_pc_11c0, { 1, 0 }
}

define i32 @while_pre_tested_loop(i32 %flag_2) local_unnamed_addr {
dec_label_pc_11f4:
  %stack_var_-24.0.lcssa.reg2mem = alloca i32, !insn.addr !36
  %stack_var_-28.01.reg2mem = alloca i32, !insn.addr !36
  %stack_var_-24.02.reg2mem = alloca i32, !insn.addr !36
  %0 = icmp slt i32 %flag_2, 0, !insn.addr !37
  store i32 0, i32* %stack_var_-24.02.reg2mem, !insn.addr !37
  store i32 0, i32* %stack_var_-28.01.reg2mem, !insn.addr !37
  store i32 0, i32* %stack_var_-24.0.lcssa.reg2mem, !insn.addr !37
  br i1 %0, label %dec_label_pc_123a, label %dec_label_pc_120f, !insn.addr !37

dec_label_pc_120f:                                ; preds = %dec_label_pc_11f4, %dec_label_pc_120f
  %stack_var_-28.01.reload = load i32, i32* %stack_var_-28.01.reg2mem
  %stack_var_-24.02.reload = load i32, i32* %stack_var_-24.02.reg2mem
  %1 = add i32 %stack_var_-24.02.reload, 7, !insn.addr !38
  %2 = add i32 %stack_var_-28.01.reload, 1, !insn.addr !39
  %3 = icmp sgt i32 %2, %flag_2, !insn.addr !37
  store i32 %1, i32* %stack_var_-24.02.reg2mem, !insn.addr !37
  store i32 %2, i32* %stack_var_-28.01.reg2mem, !insn.addr !37
  store i32 %1, i32* %stack_var_-24.0.lcssa.reg2mem, !insn.addr !37
  br i1 %3, label %dec_label_pc_123a, label %dec_label_pc_120f, !insn.addr !37

dec_label_pc_123a:                                ; preds = %dec_label_pc_120f, %dec_label_pc_11f4
  %stack_var_-24.0.lcssa.reload = load i32, i32* %stack_var_-24.0.lcssa.reg2mem
  ret i32 %stack_var_-24.0.lcssa.reload, !insn.addr !40

; uselistorder directives
  uselistorder i32* %stack_var_-24.02.reg2mem, { 2, 0, 1 }
  uselistorder i32* %stack_var_-28.01.reg2mem, { 2, 0, 1 }
  uselistorder i32 %flag_2, { 1, 0 }
  uselistorder label %dec_label_pc_120f, { 1, 0 }
}

define i32 @while_post_tested_loop(i32 %flag) local_unnamed_addr {
dec_label_pc_123f:
  %stack_var_-24.0.reg2mem = alloca i32, !insn.addr !41
  %0 = icmp slt i32 %flag, 16, !insn.addr !42
  store i32 0, i32* %stack_var_-24.0.reg2mem, !insn.addr !43
  br label %dec_label_pc_1258, !insn.addr !43

dec_label_pc_1258:                                ; preds = %dec_label_pc_1258, %dec_label_pc_123f
  %stack_var_-24.0.reload = load i32, i32* %stack_var_-24.0.reg2mem
  %1 = add i32 %stack_var_-24.0.reload, 7, !insn.addr !44
  store i32 %1, i32* %stack_var_-24.0.reg2mem, !insn.addr !42
  br i1 %0, label %dec_label_pc_1258, label %dec_label_pc_1281, !insn.addr !42

dec_label_pc_1281:                                ; preds = %dec_label_pc_1258
  ret i32 %1, !insn.addr !45

; uselistorder directives
  uselistorder i32 %1, { 1, 0 }
  uselistorder i32* %stack_var_-24.0.reg2mem, { 1, 0, 2 }
  uselistorder i32 16, { 1, 0 }
}

define i32 @main() local_unnamed_addr {
dec_label_pc_1286:
  %0 = call i32 @n_way_conditional_switch(i32 5), !insn.addr !46
  %1 = zext i32 %0 to i64, !insn.addr !47
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %1), !insn.addr !48
  %3 = call i32 @for_loop(i32 5), !insn.addr !49
  %4 = zext i32 %3 to i64, !insn.addr !50
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %4), !insn.addr !51
  %6 = call i32 @while_pre_tested_loop(i32 5), !insn.addr !52
  %7 = zext i32 %6 to i64, !insn.addr !53
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %7), !insn.addr !54
  %9 = call i32 @while_post_tested_loop(i32 5), !insn.addr !55
  %10 = zext i32 %9 to i64, !insn.addr !56
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @global_var_2004, i64 0, i64 0), i64 %10), !insn.addr !57
  ret i32 0, !insn.addr !58

; uselistorder directives
  uselistorder i32 0, { 7, 0, 1, 2, 3, 8, 4, 5, 6, 9 }
  uselistorder i32 (i8*, ...)* @printf, { 0, 1, 3, 2, 4 }
  uselistorder i64 0, { 2, 3, 5, 1, 0, 6, 4 }
  uselistorder i32 5, { 1, 2, 3, 4, 6, 0, 5 }
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1318:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !59

; uselistorder directives
  uselistorder i32 1, { 1, 2, 13, 5, 4, 3, 8, 7, 6, 11, 9, 0, 12, 10 }
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
!24 = !{i64 4443}
!25 = !{i64 4447}
!26 = !{i64 4453}
!27 = !{i64 4455}
!28 = !{i64 4459}
!29 = !{i64 4465}
!30 = !{i64 4516}
!31 = !{i64 4517}
!32 = !{i64 4589}
!33 = !{i64 4572}
!34 = !{i64 4579}
!35 = !{i64 4595}
!36 = !{i64 4596}
!37 = !{i64 4664}
!38 = !{i64 4651}
!39 = !{i64 4654}
!40 = !{i64 4670}
!41 = !{i64 4671}
!42 = !{i64 4735}
!43 = !{i64 4689}
!44 = !{i64 4724}
!45 = !{i64 4741}
!46 = !{i64 4755}
!47 = !{i64 4760}
!48 = !{i64 4777}
!49 = !{i64 4787}
!50 = !{i64 4792}
!51 = !{i64 4809}
!52 = !{i64 4819}
!53 = !{i64 4824}
!54 = !{i64 4841}
!55 = !{i64 4851}
!56 = !{i64 4856}
!57 = !{i64 4873}
!58 = !{i64 4884}
!59 = !{i64 4900}
