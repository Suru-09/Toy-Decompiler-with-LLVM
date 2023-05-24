source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2008 = constant [39 x i8] c"Is your number greater than %d ? [Y/N]\00"
@global_var_202f = constant [23 x i8] c"\0AYour number is : %d \0A\00"
@global_var_2048 = constant [41 x i8] c"Did you pick a number between 1 and 100?\00"
@global_var_2071 = constant [12 x i8] c"\0A Game over\00"
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

define i32 @function_1060(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1060:
  %0 = call i32 (i8*, ...) @printf(i8* %format), !insn.addr !7
  ret i32 %0, !insn.addr !7
}

define i32 @function_1070() local_unnamed_addr {
dec_label_pc_1070:
  %0 = call i32 @getchar(), !insn.addr !8
  ret i32 %0, !insn.addr !8
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1080:
  %stack_var_8 = alloca i64, align 8
  %0 = trunc i64 %arg6 to i32, !insn.addr !9
  %1 = bitcast i64* %stack_var_8 to i8**, !insn.addr !9
  %2 = inttoptr i64 %arg3 to void ()*, !insn.addr !9
  %3 = call i32 @__libc_start_main(i64 4597, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !9
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

define void @guess(i32 %s, i32 %d) local_unnamed_addr {
dec_label_pc_1169:
  %stack_var_-28.0.lcssa.reg2mem = alloca i32, !insn.addr !24
  %stack_var_-28.02.reg2mem = alloca i32, !insn.addr !24
  %m_-32.03.reg2mem = alloca i32, !insn.addr !24
  %0 = icmp slt i32 %s, %d, !insn.addr !25
  store i32 %d, i32* %m_-32.03.reg2mem, !insn.addr !25
  store i32 %s, i32* %stack_var_-28.02.reg2mem, !insn.addr !25
  store i32 %s, i32* %stack_var_-28.0.lcssa.reg2mem, !insn.addr !25
  br i1 %0, label %dec_label_pc_117d, label %dec_label_pc_11d9, !insn.addr !25

dec_label_pc_117d:                                ; preds = %dec_label_pc_1169, %dec_label_pc_117d
  %stack_var_-28.02.reload = load i32, i32* %stack_var_-28.02.reg2mem
  %m_-32.03.reload = load i32, i32* %m_-32.03.reg2mem
  %1 = add i32 %stack_var_-28.02.reload, %m_-32.03.reload, !insn.addr !26
  %2 = icmp slt i32 %1, 0
  %3 = zext i1 %2 to i32, !insn.addr !27
  %4 = add i32 %1, %3, !insn.addr !28
  %5 = ashr i32 %4, 1, !insn.addr !29
  %6 = zext i32 %5 to i64, !insn.addr !30
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @global_var_2008, i64 0, i64 0), i64 %6), !insn.addr !31
  %8 = call i32 @getchar(), !insn.addr !32
  %9 = call i32 @getchar(), !insn.addr !33
  %10 = icmp eq i32 %9, 89, !insn.addr !34
  %11 = icmp eq i1 %10, false, !insn.addr !35
  %12 = add nsw i32 %5, 1
  %spec.select = select i1 %11, i32 %stack_var_-28.02.reload, i32 %12
  %spec.select1 = select i1 %11, i32 %5, i32 %m_-32.03.reload
  %13 = icmp slt i32 %spec.select, %spec.select1, !insn.addr !25
  store i32 %spec.select1, i32* %m_-32.03.reg2mem, !insn.addr !25
  store i32 %spec.select, i32* %stack_var_-28.02.reg2mem, !insn.addr !25
  store i32 %spec.select, i32* %stack_var_-28.0.lcssa.reg2mem, !insn.addr !25
  br i1 %13, label %dec_label_pc_117d, label %dec_label_pc_11d9, !insn.addr !25

dec_label_pc_11d9:                                ; preds = %dec_label_pc_117d, %dec_label_pc_1169
  %stack_var_-28.0.lcssa.reload = load i32, i32* %stack_var_-28.0.lcssa.reg2mem
  %14 = zext i32 %stack_var_-28.0.lcssa.reload to i64, !insn.addr !36
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @global_var_202f, i64 0, i64 0), i64 %14), !insn.addr !37
  ret void, !insn.addr !38

; uselistorder directives
  uselistorder i32* %m_-32.03.reg2mem, { 2, 0, 1 }
  uselistorder i32* %stack_var_-28.02.reg2mem, { 2, 0, 1 }
  uselistorder label %dec_label_pc_117d, { 1, 0 }
}

define i32 @main() local_unnamed_addr {
dec_label_pc_11f5:
  %0 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @global_var_2048, i64 0, i64 0)), !insn.addr !39
  %1 = call i32 @getchar(), !insn.addr !40
  %2 = icmp eq i32 %1, 89, !insn.addr !41
  %3 = icmp eq i1 %2, false, !insn.addr !42
  br i1 %3, label %dec_label_pc_1234, label %dec_label_pc_1223, !insn.addr !42

dec_label_pc_1223:                                ; preds = %dec_label_pc_11f5
  call void @guess(i32 1, i32 100), !insn.addr !43
  br label %dec_label_pc_1248, !insn.addr !44

dec_label_pc_1234:                                ; preds = %dec_label_pc_11f5
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @global_var_2071, i64 0, i64 0)), !insn.addr !45
  br label %dec_label_pc_1248, !insn.addr !45

dec_label_pc_1248:                                ; preds = %dec_label_pc_1234, %dec_label_pc_1223
  %5 = call i32 @getchar(), !insn.addr !46
  ret i32 0, !insn.addr !47

; uselistorder directives
  uselistorder i1 false, { 1, 2, 0 }
  uselistorder i32 ()* @getchar, { 3, 0, 1, 2, 4 }
  uselistorder i64 0, { 2, 3, 4, 5, 8, 9, 6, 7, 11, 1, 0, 12, 10 }
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1258:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !48

; uselistorder directives
  uselistorder i32 1, { 1, 6, 8, 9, 4, 3, 2, 0, 7, 5 }
}

declare i32 @printf(i8*, ...) local_unnamed_addr

declare i32 @getchar() local_unnamed_addr

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
!25 = !{i64 4567}
!26 = !{i64 4483}
!27 = !{i64 4487}
!28 = !{i64 4490}
!29 = !{i64 4492}
!30 = !{i64 4500}
!31 = !{i64 4517}
!32 = !{i64 4522}
!33 = !{i64 4530}
!34 = !{i64 4538}
!35 = !{i64 4542}
!36 = !{i64 4572}
!37 = !{i64 4589}
!38 = !{i64 4596}
!39 = !{i64 4624}
!40 = !{i64 4629}
!41 = !{i64 4637}
!42 = !{i64 4641}
!43 = !{i64 4653}
!44 = !{i64 4658}
!45 = !{i64 4675}
!46 = !{i64 4680}
!47 = !{i64 4694}
!48 = !{i64 4708}
