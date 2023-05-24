; ModuleID = '../testing_files/elfC/bsearch.ll'
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

define void @function_1050(i64* %d) local_unnamed_addr {
dec_label_pc_1050:
  call void @__cxa_finalize(i64* %d), !insn.addr !5
  ret void, !insn.addr !5
}

define i32 @function_1060(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1060:
  %i = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) %format), !insn.addr !6
  ret i32 %i, !insn.addr !6
}

define i32 @function_1070() local_unnamed_addr {
dec_label_pc_1070:
  %i = call i32 @getchar(), !insn.addr !7
  ret i32 %i, !insn.addr !7
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1080:
  %stack_var_8 = alloca i8*, align 8
  %i = trunc i64 %arg6 to i32, !insn.addr !8
  %i1 = inttoptr i64 %arg3 to void ()*, !insn.addr !8
  %i2 = call i32 @__libc_start_main(i64 4597, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !8
  %i3 = call i64 @__asm_hlt(), !insn.addr !9
  unreachable, !insn.addr !9
}

define i64 @deregister_tm_clones() local_unnamed_addr {
dec_label_pc_10b0:
  ret i64 ptrtoint (i64* @global_var_4010 to i64), !insn.addr !10
}

define i64 @register_tm_clones() local_unnamed_addr {
dec_label_pc_10e0:
  ret i64 0, !insn.addr !11
}

define i64 @__do_global_dtors_aux() local_unnamed_addr {
dec_label_pc_1120:
  %i1 = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !12
  %.not = icmp eq i8 %i1, 0, !insn.addr !12
  br i1 %.not, label %dec_label_pc_112d, label %dec_label_pc_1158, !insn.addr !13

dec_label_pc_112d:                                ; preds = %dec_label_pc_1120
  %i2 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !14
  %i3 = icmp eq i64 %i2, 0, !insn.addr !14
  br i1 %i3, label %dec_label_pc_1147, label %dec_label_pc_113b, !insn.addr !15

dec_label_pc_113b:                                ; preds = %dec_label_pc_112d
  %i4 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !16
  %i5 = inttoptr i64 %i4 to i64*, !insn.addr !17
  call void @__cxa_finalize(i64* %i5), !insn.addr !17
  br label %dec_label_pc_1147, !insn.addr !17

common.ret:                                       ; preds = %dec_label_pc_1158, %dec_label_pc_1147
  %common.ret.op = phi i64 [ %i6, %dec_label_pc_1147 ], [ undef, %dec_label_pc_1158 ]
  ret i64 %common.ret.op, !insn.addr !18

dec_label_pc_1147:                                ; preds = %dec_label_pc_113b, %dec_label_pc_112d
  %i6 = call i64 @deregister_tm_clones(), !insn.addr !19
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !20
  br label %common.ret

dec_label_pc_1158:                                ; preds = %dec_label_pc_1120
  br label %common.ret
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1160:
  %i = call i64 @register_tm_clones(), !insn.addr !21
  ret i64 %i, !insn.addr !21
}

define void @guess(i32 %s, i32 %d) local_unnamed_addr {
dec_label_pc_1169:
  %i = icmp slt i32 %s, %d, !insn.addr !22
  br i1 %i, label %dec_label_pc_117d.preheader, label %dec_label_pc_11d9, !insn.addr !22

dec_label_pc_117d.preheader:                      ; preds = %dec_label_pc_1169
  br label %dec_label_pc_117d

dec_label_pc_117d:                                ; preds = %dec_label_pc_117d.preheader, %dec_label_pc_117d
  %m_-32.03.reg2mem.0 = phi i32 [ %d, %dec_label_pc_117d.preheader ], [ %spec.select1, %dec_label_pc_117d ]
  %stack_var_-28.02.reg2mem.0 = phi i32 [ %s, %dec_label_pc_117d.preheader ], [ %spec.select, %dec_label_pc_117d ]
  %i1 = add i32 %m_-32.03.reg2mem.0, %stack_var_-28.02.reg2mem.0, !insn.addr !23
  %.lobit = lshr i32 %i1, 31
  %i2 = add i32 %.lobit, %i1, !insn.addr !24
  %i3 = ashr i32 %i2, 1, !insn.addr !25
  %i4 = zext i32 %i3 to i64, !insn.addr !26
  %i5 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([39 x i8], [39 x i8]* @global_var_2008, i64 0, i64 0), i64 %i4), !insn.addr !27
  %i6 = call i32 @getchar(), !insn.addr !28
  %i7 = call i32 @getchar(), !insn.addr !29
  %.not = icmp eq i32 %i7, 89, !insn.addr !30
  %i8 = add nsw i32 %i3, 1
  %spec.select = select i1 %.not, i32 %i8, i32 %stack_var_-28.02.reg2mem.0
  %spec.select1 = select i1 %.not, i32 %m_-32.03.reg2mem.0, i32 %i3
  %i9 = icmp slt i32 %spec.select, %spec.select1, !insn.addr !22
  br i1 %i9, label %dec_label_pc_117d, label %dec_label_pc_11d9.loopexit, !insn.addr !22

dec_label_pc_11d9.loopexit:                       ; preds = %dec_label_pc_117d
  br label %dec_label_pc_11d9

dec_label_pc_11d9:                                ; preds = %dec_label_pc_11d9.loopexit, %dec_label_pc_1169
  %stack_var_-28.0.lcssa.reg2mem.0 = phi i32 [ %spec.select, %dec_label_pc_11d9.loopexit ], [ %s, %dec_label_pc_1169 ]
  %i10 = zext i32 %stack_var_-28.0.lcssa.reg2mem.0 to i64, !insn.addr !31
  %i11 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([23 x i8], [23 x i8]* @global_var_202f, i64 0, i64 0), i64 %i10), !insn.addr !32
  ret void, !insn.addr !33
}

define i32 @main() local_unnamed_addr {
dec_label_pc_11f5:
  %i = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([41 x i8], [41 x i8]* @global_var_2048, i64 0, i64 0)), !insn.addr !34
  %i1 = call i32 @getchar(), !insn.addr !35
  %.not = icmp eq i32 %i1, 89, !insn.addr !36
  br i1 %.not, label %dec_label_pc_1223, label %dec_label_pc_1234, !insn.addr !37

dec_label_pc_1223:                                ; preds = %dec_label_pc_11f5
  call void @guess(i32 1, i32 100), !insn.addr !38
  br label %dec_label_pc_1248, !insn.addr !39

dec_label_pc_1234:                                ; preds = %dec_label_pc_11f5
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([12 x i8], [12 x i8]* @global_var_2071, i64 0, i64 0)), !insn.addr !40
  br label %dec_label_pc_1248, !insn.addr !40

dec_label_pc_1248:                                ; preds = %dec_label_pc_1234, %dec_label_pc_1223
  %i3 = call i32 @getchar(), !insn.addr !41
  ret i32 0, !insn.addr !42
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1258:
  ret i64 undef, !insn.addr !43
}

declare i32 @printf(i8*, ...) local_unnamed_addr

declare i32 @getchar() local_unnamed_addr

declare i32 @__libc_start_main(i64, i32, i8**, void ()*, void ()*, void ()*) local_unnamed_addr

declare void @__gmon_start__() local_unnamed_addr

declare void @__cxa_finalize(i64*) local_unnamed_addr

declare i64 @__asm_hlt() local_unnamed_addr

!0 = !{i64 4104}
!1 = !{i64 4111}
!2 = !{i64 4114}
!3 = !{i64 4116}
!4 = !{i64 4122}
!5 = !{i64 4180}
!6 = !{i64 4196}
!7 = !{i64 4212}
!8 = !{i64 4255}
!9 = !{i64 4261}
!10 = !{i64 4312}
!11 = !{i64 4376}
!12 = !{i64 4388}
!13 = !{i64 4395}
!14 = !{i64 4398}
!15 = !{i64 4409}
!16 = !{i64 4411}
!17 = !{i64 4418}
!18 = !{i64 4436}
!19 = !{i64 4423}
!20 = !{i64 4428}
!21 = !{i64 4452}
!22 = !{i64 4567}
!23 = !{i64 4483}
!24 = !{i64 4490}
!25 = !{i64 4492}
!26 = !{i64 4500}
!27 = !{i64 4517}
!28 = !{i64 4522}
!29 = !{i64 4530}
!30 = !{i64 4538}
!31 = !{i64 4572}
!32 = !{i64 4589}
!33 = !{i64 4596}
!34 = !{i64 4624}
!35 = !{i64 4629}
!36 = !{i64 4637}
!37 = !{i64 4641}
!38 = !{i64 4653}
!39 = !{i64 4658}
!40 = !{i64 4675}
!41 = !{i64 4680}
!42 = !{i64 4694}
!43 = !{i64 4708}
