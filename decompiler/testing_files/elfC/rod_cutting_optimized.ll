; ModuleID = '../testing_files/elfC/rod_cutting.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

@global_var_4010 = global i64 0
@global_var_2008 = constant [21 x i8] c"Enter the n value : \00"
@global_var_201d = constant [3 x i8] c"%d\00"
@global_var_2020 = constant [26 x i8] c"The array of prices is : \00"
@global_var_203a = constant [5 x i8] c" %d \00"
@global_var_2040 = constant [37 x i8] c"\0AThe best value you can get is : %d\0A\00"
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

define void @function_10b0(i64* %d) local_unnamed_addr {
dec_label_pc_10b0:
  call void @__cxa_finalize(i64* %d), !insn.addr !5
  ret void, !insn.addr !5
}

define i32 @function_10c0(i8* %s) local_unnamed_addr {
dec_label_pc_10c0:
  %i = call i32 @puts(i8* noundef nonnull dereferenceable(1) %s), !insn.addr !6
  ret i32 %i, !insn.addr !6
}

define void @function_10d0() local_unnamed_addr {
dec_label_pc_10d0:
  call void @__stack_chk_fail(), !insn.addr !7
  ret void, !insn.addr !7
}

define i32 @function_10e0(i8* %format, ...) local_unnamed_addr {
dec_label_pc_10e0:
  %i = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) %format), !insn.addr !8
  ret i32 %i, !insn.addr !8
}

define i64* @function_10f0(i64* %s, i32 %c, i32 %n) local_unnamed_addr {
dec_label_pc_10f0:
  %i = call i64* @memset(i64* %s, i32 %c, i32 %n), !insn.addr !9
  ret i64* %i, !insn.addr !9
}

define void @function_1100(i32 %seed) local_unnamed_addr {
dec_label_pc_1100:
  call void @srand(i32 %seed), !insn.addr !10
  ret void, !insn.addr !10
}

define i32 @function_1110(i32* %timer) local_unnamed_addr {
dec_label_pc_1110:
  %i = call i32 @time(i32* %timer), !insn.addr !11
  ret i32 %i, !insn.addr !11
}

define i32 @function_1120(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1120:
  %i = call i32 (i8*, ...) @scanf(i8* %format), !insn.addr !12
  ret i32 %i, !insn.addr !12
}

define i32 @function_1130() local_unnamed_addr {
dec_label_pc_1130:
  %i = call i32 @rand(), !insn.addr !13
  ret i32 %i, !insn.addr !13
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1140:
  %stack_var_8 = alloca i8*, align 8
  %i = trunc i64 %arg6 to i32, !insn.addr !14
  %i1 = inttoptr i64 %arg3 to void ()*, !insn.addr !14
  %i2 = call i32 @__libc_start_main(i64 5221, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !14
  %i3 = call i64 @__asm_hlt(), !insn.addr !15
  unreachable, !insn.addr !15
}

define i64 @deregister_tm_clones() local_unnamed_addr {
dec_label_pc_1170:
  ret i64 ptrtoint (i64* @global_var_4010 to i64), !insn.addr !16
}

define i64 @register_tm_clones() local_unnamed_addr {
dec_label_pc_11a0:
  ret i64 0, !insn.addr !17
}

define i64 @__do_global_dtors_aux() local_unnamed_addr {
dec_label_pc_11e0:
  %i1 = load i8, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !18
  %.not = icmp eq i8 %i1, 0, !insn.addr !18
  br i1 %.not, label %dec_label_pc_11ed, label %dec_label_pc_1218, !insn.addr !19

dec_label_pc_11ed:                                ; preds = %dec_label_pc_11e0
  %i2 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !20
  %i3 = icmp eq i64 %i2, 0, !insn.addr !20
  br i1 %i3, label %dec_label_pc_1207, label %dec_label_pc_11fb, !insn.addr !21

dec_label_pc_11fb:                                ; preds = %dec_label_pc_11ed
  %i4 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !22
  %i5 = inttoptr i64 %i4 to i64*, !insn.addr !23
  call void @__cxa_finalize(i64* %i5), !insn.addr !23
  br label %dec_label_pc_1207, !insn.addr !23

common.ret:                                       ; preds = %dec_label_pc_1218, %dec_label_pc_1207
  %common.ret.op = phi i64 [ %i6, %dec_label_pc_1207 ], [ undef, %dec_label_pc_1218 ]
  ret i64 %common.ret.op, !insn.addr !24

dec_label_pc_1207:                                ; preds = %dec_label_pc_11fb, %dec_label_pc_11ed
  %i6 = call i64 @deregister_tm_clones(), !insn.addr !25
  store i8 1, i8* bitcast (i64* @global_var_4010 to i8*), align 8, !insn.addr !26
  br label %common.ret

dec_label_pc_1218:                                ; preds = %dec_label_pc_11e0
  br label %common.ret
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1220:
  %i = call i64 @register_tm_clones(), !insn.addr !27
  ret i64 %i, !insn.addr !27
}

define void @generate_price_array(i32 %n, i32* %price) local_unnamed_addr {
dec_label_pc_1229:
  %i = call i32 @time(i32* null), !insn.addr !28
  call void @srand(i32 %i), !insn.addr !29
  %i1 = icmp sgt i32 %n, 0, !insn.addr !30
  br i1 %i1, label %dec_label_pc_1256.lr.ph, label %dec_label_pc_129d, !insn.addr !30

dec_label_pc_1256.lr.ph:                          ; preds = %dec_label_pc_1229
  %i2 = ptrtoint i32* %price to i64
  %wide.trip.count = zext i32 %n to i64
  br label %dec_label_pc_1256

dec_label_pc_1256:                                ; preds = %dec_label_pc_1256, %dec_label_pc_1256.lr.ph
  %indvars.iv.reg2mem.0 = phi i64 [ 0, %dec_label_pc_1256.lr.ph ], [ %indvars.iv.next, %dec_label_pc_1256 ]
  %i3 = call i32 @rand(), !insn.addr !31
  %i4 = shl i64 %indvars.iv.reg2mem.0, 2
  %i5 = add i64 %i4, %i2, !insn.addr !32
  %i6 = srem i32 %i3, 100
  %i7 = inttoptr i64 %i5 to i32*, !insn.addr !33
  store i32 %i6, i32* %i7, align 4, !insn.addr !33
  %indvars.iv.next = add nuw nsw i64 %indvars.iv.reg2mem.0, 1
  %exitcond = icmp eq i64 %indvars.iv.next, %wide.trip.count
  br i1 %exitcond, label %dec_label_pc_129d.loopexit, label %dec_label_pc_1256, !insn.addr !30

dec_label_pc_129d.loopexit:                       ; preds = %dec_label_pc_1256
  br label %dec_label_pc_129d

dec_label_pc_129d:                                ; preds = %dec_label_pc_129d.loopexit, %dec_label_pc_1229
  ret void, !insn.addr !34
}

define i32 @maxi(i32 %a, i32 %b) local_unnamed_addr {
dec_label_pc_12a1:
  %i = icmp sgt i32 %a, %b, !insn.addr !35
  %storemerge.in = select i1 %i, i32 %a, i32 %b
  ret i32 %storemerge.in, !insn.addr !36
}

define i32 @rod_cutting(i32 %n, i32* %price) local_unnamed_addr {
dec_label_pc_12c1:
  %array_ways_-56 = alloca [1 x i32], align 4
  %stack_var_-88 = alloca i32*, align 8
  %i = ptrtoint i32** %stack_var_-88 to i64, !insn.addr !37
  store i32* %price, i32** %stack_var_-88, align 8, !insn.addr !38
  %i1 = call i64 @__readfsqword(i64 40), !insn.addr !39
  %i2 = add i32 %n, 1, !insn.addr !40
  %i3 = sext i32 %i2 to i64, !insn.addr !41
  %i4 = shl nsw i64 %i3, 2
  %i5 = add nsw i64 %i4, 15, !insn.addr !42
  %i6 = and i64 %i5, -16
  %i7 = sub i64 %i, %i6
  %i8 = shl i32 %n, 2
  %i9 = add i32 %i8, 4, !insn.addr !43
  %i10 = inttoptr i64 %i7 to i64*, !insn.addr !44
  %i11 = call i64* @memset(i64* %i10, i32 0, i32 %i9), !insn.addr !44
  %i12 = icmp slt i32 %n, 1, !insn.addr !45
  br i1 %i12, label %dec_label_pc_143b, label %dec_label_pc_13c8.lr.ph, !insn.addr !45

dec_label_pc_13c8.lr.ph:                          ; preds = %dec_label_pc_12c1
  %i13 = getelementptr inbounds [1 x i32], [1 x i32]* %array_ways_-56, i64 0, i64 0
  br label %dec_label_pc_13c8

dec_label_pc_13c8:                                ; preds = %dec_label_pc_13c8.lr.ph, %dec_label_pc_142f
  %storemerge4.reg2mem.0 = phi i32 [ 1, %dec_label_pc_13c8.lr.ph ], [ %i38, %dec_label_pc_142f ]
  %i14 = getelementptr inbounds [1 x i32], [1 x i32]* %array_ways_-56, i64 0, i64 0
  store i32 -2147483648, i32* %i14, align 4
  %i15 = icmp sgt i32 %storemerge4.reg2mem.0, 0, !insn.addr !46
  br i1 %i15, label %dec_label_pc_13d8.lr.ph, label %dec_label_pc_142f, !insn.addr !46

dec_label_pc_13d8.lr.ph:                          ; preds = %dec_label_pc_13c8
  %i16 = sext i32 %storemerge4.reg2mem.0 to i64
  %i17 = shl nsw i64 %i16, 2
  %i18 = add i64 %i17, %i7
  %i19 = inttoptr i64 %i18 to i32*
  %wide.trip.count = zext i32 %storemerge4.reg2mem.0 to i64
  br label %dec_label_pc_13d8

dec_label_pc_13d8:                                ; preds = %dec_label_pc_13d8, %dec_label_pc_13d8.lr.ph
  %indvars.iv.reg2mem.0 = phi i64 [ 0, %dec_label_pc_13d8.lr.ph ], [ %indvars.iv.next, %dec_label_pc_13d8 ]
  %i20 = shl i64 %indvars.iv.reg2mem.0, 2
  %i21 = load i32*, i32** %stack_var_-88, align 8, !insn.addr !47
  %i22 = ptrtoint i32* %i21 to i64, !insn.addr !47
  %i23 = add i64 %i20, %i22, !insn.addr !48
  %i24 = inttoptr i64 %i23 to i32*, !insn.addr !49
  %i25 = load i32, i32* %i24, align 4, !insn.addr !49
  %i26 = trunc i64 %indvars.iv.reg2mem.0 to i32
  %i27 = xor i32 %i26, -1
  %i28 = add i32 %storemerge4.reg2mem.0, %i27
  %i29 = sext i32 %i28 to i64, !insn.addr !50
  %i30 = shl nsw i64 %i29, 2
  %i31 = add i64 %i30, %i7, !insn.addr !51
  %i32 = inttoptr i64 %i31 to i32*, !insn.addr !51
  %i33 = load i32, i32* %i32, align 4, !insn.addr !51
  %i34 = add i32 %i33, %i25, !insn.addr !52
  %i35 = load i32, i32* %i13, align 4, !insn.addr !53
  %i36 = call i32 @maxi(i32 %i34, i32 %i35), !insn.addr !54
  %i37 = getelementptr inbounds [1 x i32], [1 x i32]* %array_ways_-56, i64 0, i64 0
  store i32 %i36, i32* %i37, align 4
  store i32 %i36, i32* %i19, align 4, !insn.addr !55
  %indvars.iv.next = add nuw nsw i64 %indvars.iv.reg2mem.0, 1
  %exitcond = icmp eq i64 %indvars.iv.next, %wide.trip.count
  br i1 %exitcond, label %dec_label_pc_142f.loopexit, label %dec_label_pc_13d8, !insn.addr !46

dec_label_pc_142f.loopexit:                       ; preds = %dec_label_pc_13d8
  br label %dec_label_pc_142f

dec_label_pc_142f:                                ; preds = %dec_label_pc_142f.loopexit, %dec_label_pc_13c8
  %i38 = add i32 %storemerge4.reg2mem.0, 1, !insn.addr !56
  %i39 = icmp sgt i32 %i38, %n, !insn.addr !45
  br i1 %i39, label %dec_label_pc_143b.loopexit, label %dec_label_pc_13c8, !insn.addr !45

dec_label_pc_143b.loopexit:                       ; preds = %dec_label_pc_142f
  br label %dec_label_pc_143b

dec_label_pc_143b:                                ; preds = %dec_label_pc_143b.loopexit, %dec_label_pc_12c1
  %i40 = sext i32 %n to i64, !insn.addr !57
  %i41 = shl nsw i64 %i40, 2
  %i42 = add i64 %i7, %i41, !insn.addr !58
  %i43 = inttoptr i64 %i42 to i32*, !insn.addr !58
  %i44 = load i32, i32* %i43, align 4, !insn.addr !58
  %i45 = call i64 @__readfsqword(i64 40), !insn.addr !59
  %i46 = icmp eq i64 %i1, %i45, !insn.addr !59
  br i1 %i46, label %dec_label_pc_145f, label %dec_label_pc_145a, !insn.addr !60

dec_label_pc_145a:                                ; preds = %dec_label_pc_143b
  call void @__stack_chk_fail(), !insn.addr !61
  br label %dec_label_pc_145f, !insn.addr !61

dec_label_pc_145f:                                ; preds = %dec_label_pc_145a, %dec_label_pc_143b
  %rax.0.reg2mem.0 = phi i32 [ %i44, %dec_label_pc_143b ], [ ptrtoint (i32* @0 to i32), %dec_label_pc_145a ]
  ret i32 %rax.0.reg2mem.0, !insn.addr !62
}

define i32 @main() local_unnamed_addr {
dec_label_pc_1465:
  %stack_var_-88 = alloca i64, align 8
  %i = ptrtoint i64* %stack_var_-88 to i64, !insn.addr !63
  %i1 = call i64 @__readfsqword(i64 40), !insn.addr !64
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([21 x i8], [21 x i8]* @global_var_2008, i64 0, i64 0)), !insn.addr !65
  %i3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_var_201d, i64 0, i64 0), i64* nonnull %stack_var_-88), !insn.addr !66
  %i4 = load i64, i64* %stack_var_-88, align 8
  %sext = shl i64 %i4, 32
  %i5 = ashr exact i64 %sext, 30, !insn.addr !67
  %i6 = add nsw i64 %i5, 15, !insn.addr !68
  %i7 = and i64 %i6, -16
  %i8 = sub i64 %i, %i7
  %i9 = inttoptr i64 %i8 to i32*, !insn.addr !69
  %i10 = trunc i64 %i4 to i32, !insn.addr !70
  call void @generate_price_array(i32 %i10, i32* %i9), !insn.addr !71
  %i11 = call i32 @puts(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([26 x i8], [26 x i8]* @global_var_2020, i64 0, i64 0)), !insn.addr !72
  %i12 = load i64, i64* %stack_var_-88, align 8, !insn.addr !73
  %i13 = and i64 %i12, 4294967295, !insn.addr !73
  %i14 = icmp eq i64 %i13, 0, !insn.addr !74
  br i1 %i14, label %dec_label_pc_15c7, label %dec_label_pc_1598.preheader, !insn.addr !74

dec_label_pc_1598.preheader:                      ; preds = %dec_label_pc_1465
  br label %dec_label_pc_1598

dec_label_pc_1598:                                ; preds = %dec_label_pc_1598.preheader, %dec_label_pc_1598
  %.reg2mem.0 = phi i64 [ 0, %dec_label_pc_1598.preheader ], [ %i24, %dec_label_pc_1598 ]
  %storemerge2.reg2mem.0 = phi i32 [ 0, %dec_label_pc_1598.preheader ], [ %i21, %dec_label_pc_1598 ]
  %i15 = shl i64 %.reg2mem.0, 2
  %i16 = add i64 %i15, %i8, !insn.addr !75
  %i17 = inttoptr i64 %i16 to i32*, !insn.addr !75
  %i18 = load i32, i32* %i17, align 4, !insn.addr !75
  %i19 = zext i32 %i18 to i64, !insn.addr !76
  %i20 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([5 x i8], [5 x i8]* @global_var_203a, i64 0, i64 0), i64 %i19), !insn.addr !77
  %i21 = add i32 %storemerge2.reg2mem.0, 1, !insn.addr !78
  %i22 = load i64, i64* %stack_var_-88, align 8, !insn.addr !73
  %i23 = and i64 %i22, 4294967295, !insn.addr !73
  %i24 = sext i32 %i21 to i64, !insn.addr !74
  %i25 = icmp sgt i64 %i23, %i24, !insn.addr !74
  br i1 %i25, label %dec_label_pc_1598, label %dec_label_pc_15c7.loopexit, !insn.addr !74

dec_label_pc_15c7.loopexit:                       ; preds = %dec_label_pc_1598
  br label %dec_label_pc_15c7

dec_label_pc_15c7:                                ; preds = %dec_label_pc_15c7.loopexit, %dec_label_pc_1465
  %.lcssa.reg2mem.0 = phi i64 [ %i12, %dec_label_pc_1465 ], [ %i22, %dec_label_pc_15c7.loopexit ]
  %i26 = trunc i64 %.lcssa.reg2mem.0 to i32, !insn.addr !79
  %i27 = call i32 @rod_cutting(i32 %i26, i32* %i9), !insn.addr !80
  %i28 = zext i32 %i27 to i64, !insn.addr !81
  %i29 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([37 x i8], [37 x i8]* @global_var_2040, i64 0, i64 0), i64 %i28), !insn.addr !82
  %i30 = call i64 @__readfsqword(i64 40), !insn.addr !83
  %i31 = icmp eq i64 %i1, %i30, !insn.addr !83
  br i1 %i31, label %dec_label_pc_160a, label %dec_label_pc_1605, !insn.addr !84

dec_label_pc_1605:                                ; preds = %dec_label_pc_15c7
  call void @__stack_chk_fail(), !insn.addr !85
  br label %dec_label_pc_160a, !insn.addr !85

dec_label_pc_160a:                                ; preds = %dec_label_pc_1605, %dec_label_pc_15c7
  %rax.0.reg2mem.0 = phi i32 [ 0, %dec_label_pc_15c7 ], [ ptrtoint (i32* @0 to i32), %dec_label_pc_1605 ]
  ret i32 %rax.0.reg2mem.0, !insn.addr !86
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_161c:
  ret i64 undef, !insn.addr !87
}

declare i32 @puts(i8*) local_unnamed_addr

declare void @__stack_chk_fail() local_unnamed_addr

declare i32 @printf(i8*, ...) local_unnamed_addr

declare i64* @memset(i64*, i32, i32) local_unnamed_addr

declare void @srand(i32) local_unnamed_addr

declare i32 @time(i32*) local_unnamed_addr

declare i32 @scanf(i8*, ...) local_unnamed_addr

declare i32 @rand() local_unnamed_addr

declare i32 @__libc_start_main(i64, i32, i8**, void ()*, void ()*, void ()*) local_unnamed_addr

declare void @__gmon_start__() local_unnamed_addr

declare void @__cxa_finalize(i64*) local_unnamed_addr

declare i64 @__asm_hlt() local_unnamed_addr

declare i64 @__readfsqword(i64) local_unnamed_addr

!0 = !{i64 4104}
!1 = !{i64 4111}
!2 = !{i64 4114}
!3 = !{i64 4116}
!4 = !{i64 4122}
!5 = !{i64 4276}
!6 = !{i64 4292}
!7 = !{i64 4308}
!8 = !{i64 4324}
!9 = !{i64 4340}
!10 = !{i64 4356}
!11 = !{i64 4372}
!12 = !{i64 4388}
!13 = !{i64 4404}
!14 = !{i64 4447}
!15 = !{i64 4453}
!16 = !{i64 4504}
!17 = !{i64 4568}
!18 = !{i64 4580}
!19 = !{i64 4587}
!20 = !{i64 4590}
!21 = !{i64 4601}
!22 = !{i64 4603}
!23 = !{i64 4610}
!24 = !{i64 4628}
!25 = !{i64 4615}
!26 = !{i64 4620}
!27 = !{i64 4644}
!28 = !{i64 4673}
!29 = !{i64 4680}
!30 = !{i64 4763}
!31 = !{i64 4694}
!32 = !{i64 4717}
!33 = !{i64 4751}
!34 = !{i64 4768}
!35 = !{i64 4789}
!36 = !{i64 4800}
!37 = !{i64 4810}
!38 = !{i64 4817}
!39 = !{i64 4821}
!40 = !{i64 4845}
!41 = !{i64 4883}
!42 = !{i64 4902}
!43 = !{i64 5030}
!44 = !{i64 5050}
!45 = !{i64 5177}
!46 = !{i64 5165}
!47 = !{i64 5093}
!48 = !{i64 5097}
!49 = !{i64 5100}
!50 = !{i64 5115}
!51 = !{i64 5118}
!52 = !{i64 5121}
!53 = !{i64 5124}
!54 = !{i64 5131}
!55 = !{i64 5152}
!56 = !{i64 5167}
!57 = !{i64 5186}
!58 = !{i64 5189}
!59 = !{i64 5199}
!60 = !{i64 5208}
!61 = !{i64 5210}
!62 = !{i64 5220}
!63 = !{i64 5238}
!64 = !{i64 5242}
!65 = !{i64 5278}
!66 = !{i64 5305}
!67 = !{i64 5350}
!68 = !{i64 5367}
!69 = !{i64 5483}
!70 = !{i64 5487}
!71 = !{i64 5499}
!72 = !{i64 5514}
!73 = !{i64 5567}
!74 = !{i64 5573}
!75 = !{i64 5538}
!76 = !{i64 5541}
!77 = !{i64 5558}
!78 = !{i64 5563}
!79 = !{i64 5575}
!80 = !{i64 5587}
!81 = !{i64 5592}
!82 = !{i64 5609}
!83 = !{i64 5626}
!84 = !{i64 5635}
!85 = !{i64 5637}
!86 = !{i64 5656}
!87 = !{i64 5672}
