; ModuleID = '../testing_files/elfC/test.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2004 = constant [20 x i8] c"Value of sum: <%d>\0A\00"
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
  %i = call i32 (i8*, ...) @printf(i8* %format), !insn.addr !6
  ret i32 %i, !insn.addr !6
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1060:
  %stack_var_8 = alloca i64, align 8
  %i = trunc i64 %arg6 to i32, !insn.addr !7
  %i1 = bitcast i64* %stack_var_8 to i8**, !insn.addr !7
  %i2 = inttoptr i64 %arg3 to void ()*, !insn.addr !7
  %i3 = call i32 @__libc_start_main(i64 4522, i32 %i, i8** nonnull %i1, void ()* null, void ()* null, void ()* %i2), !insn.addr !7
  %i4 = call i64 @__asm_hlt(), !insn.addr !8
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
  %i = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !11
  %i1 = icmp eq i8 %i, 0, !insn.addr !11
  %i2 = icmp eq i1 %i1, false, !insn.addr !12
  br i1 %i2, label %dec_label_pc_1138, label %dec_label_pc_110d, !insn.addr !12

dec_label_pc_110d:                                ; preds = %dec_label_pc_1100
  %i3 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !13
  %i4 = icmp eq i64 %i3, 0, !insn.addr !13
  br i1 %i4, label %dec_label_pc_1127, label %dec_label_pc_111b, !insn.addr !14

dec_label_pc_111b:                                ; preds = %dec_label_pc_110d
  %i5 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !15
  %i6 = inttoptr i64 %i5 to i64*, !insn.addr !16
  call void @__cxa_finalize(i64* %i6), !insn.addr !16
  br label %dec_label_pc_1127, !insn.addr !16

dec_label_pc_1127:                                ; preds = %dec_label_pc_111b, %dec_label_pc_110d
  %i7 = call i64 @deregister_tm_clones(), !insn.addr !17
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !18
  ret i64 %i7, !insn.addr !19

dec_label_pc_1138:                                ; preds = %dec_label_pc_1100
  ret i64 undef, !insn.addr !20
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1140:
  %i = call i64 @register_tm_clones(), !insn.addr !21
  ret i64 %i, !insn.addr !21
}

define i32 @calc_sum(i32 %n) local_unnamed_addr {
dec_label_pc_1149:
  %i = icmp sgt i32 %n, 0, !insn.addr !22
  br i1 %i, label %dec_label_pc_1188.preheader.lr.ph, label %dec_label_pc_11a5, !insn.addr !22

dec_label_pc_1188.preheader.lr.ph:                ; preds = %dec_label_pc_1149
  %i1 = ashr i32 %n, 1, !insn.addr !23
  %i2 = zext i32 %i1 to i64, !insn.addr !23
  %i3 = icmp eq i32 %i1, 0, !insn.addr !24
  br label %dec_label_pc_1188.preheader

dec_label_pc_116d:                                ; preds = %dec_label_pc_116d.lr.ph, %dec_label_pc_116d
  %stack_var_-20.12.reg2mem.0 = phi i32 [ %stack_var_-20.25.reg2mem.0, %dec_label_pc_116d.lr.ph ], [ %stack_var_-20.0, %dec_label_pc_116d ]
  %storemerge13.reg2mem.0 = phi i32 [ 0, %dec_label_pc_116d.lr.ph ], [ %i6, %dec_label_pc_116d ]
  %i4 = add i32 %storemerge13.reg2mem.0, %i11
  %i5 = select i1 %i10, i32 0, i32 %i4
  %stack_var_-20.0 = add i32 %stack_var_-20.12.reg2mem.0, %i5
  %i6 = add i32 %storemerge13.reg2mem.0, 1, !insn.addr !25
  %i7 = sext i32 %i6 to i64, !insn.addr !24
  %i8 = icmp slt i64 %i7, %i2, !insn.addr !24
  br i1 %i8, label %dec_label_pc_116d, label %dec_label_pc_1199, !insn.addr !24

dec_label_pc_1199:                                ; preds = %dec_label_pc_116d, %dec_label_pc_1188.preheader
  %stack_var_-20.1.lcssa.reg2mem.0 = phi i32 [ %stack_var_-20.25.reg2mem.0, %dec_label_pc_1188.preheader ], [ %stack_var_-20.0, %dec_label_pc_116d ]
  %i9 = add nuw nsw i32 %storemerge6.reg2mem.0, 1, !insn.addr !26
  %exitcond = icmp eq i32 %i9, %n
  br i1 %exitcond, label %dec_label_pc_11a5, label %dec_label_pc_1188.preheader, !insn.addr !22

dec_label_pc_1188.preheader:                      ; preds = %dec_label_pc_1199, %dec_label_pc_1188.preheader.lr.ph
  %stack_var_-20.25.reg2mem.0 = phi i32 [ 0, %dec_label_pc_1188.preheader.lr.ph ], [ %stack_var_-20.1.lcssa.reg2mem.0, %dec_label_pc_1199 ]
  %storemerge6.reg2mem.0 = phi i32 [ 0, %dec_label_pc_1188.preheader.lr.ph ], [ %i9, %dec_label_pc_1199 ]
  br i1 %i3, label %dec_label_pc_1199, label %dec_label_pc_116d.lr.ph, !insn.addr !24

dec_label_pc_116d.lr.ph:                          ; preds = %dec_label_pc_1188.preheader
  %i10 = icmp ult i32 %storemerge6.reg2mem.0, 3, !insn.addr !27
  %i11 = mul i32 %storemerge6.reg2mem.0, 3
  br label %dec_label_pc_116d

dec_label_pc_11a5:                                ; preds = %dec_label_pc_1199, %dec_label_pc_1149
  %stack_var_-20.2.lcssa.reg2mem.0 = phi i32 [ %stack_var_-20.1.lcssa.reg2mem.0, %dec_label_pc_1199 ], [ 0, %dec_label_pc_1149 ]
  ret i32 %stack_var_-20.2.lcssa.reg2mem.0, !insn.addr !28
}

define i32 @main() local_unnamed_addr {
dec_label_pc_11aa:
  %i = call i32 @calc_sum(i32 10), !insn.addr !29
  %i1 = zext i32 %i to i64, !insn.addr !30
  %i2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @global_var_2004, i64 0, i64 0), i64 %i1), !insn.addr !31
  ret i32 0, !insn.addr !32
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_11dc:
  ret i64 undef, !insn.addr !33
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
!17 = !{i64 4391}
!18 = !{i64 4396}
!19 = !{i64 4404}
!20 = !{i64 4408}
!21 = !{i64 4420}
!22 = !{i64 4515}
!23 = !{i64 4498}
!24 = !{i64 4503}
!25 = !{i64 4484}
!26 = !{i64 4505}
!27 = !{i64 4465}
!28 = !{i64 4521}
!29 = !{i64 4535}
!30 = !{i64 4540}
!31 = !{i64 4557}
!32 = !{i64 4568}
!33 = !{i64 4584}
