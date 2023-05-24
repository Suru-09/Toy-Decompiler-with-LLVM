; ModuleID = '../testing_files/elfC/tower_hanoi.ll'
source_filename = "test"
target datalayout = "e-m:e-p:64:64-i64:64-f80:128-n8:16:32:64-S128"

%_IO_FILE = type { i32 }

@global_var_4018 = global i64 0
@global_var_2008 = constant [22 x i8] c"Disk 1 from %d to %d\0A\00"
@global_var_201e = constant [23 x i8] c"Disk %d from %d to %d\0A\00"
@global_var_2038 = constant [105 x i8] c"<svg width =\221920\22 height =\222300\22 xmlns=\22http://www.w3.org/2000/svg\22 version=\221.1\22 overflow =\22auto\22 > \0A\0A\00"
@y = local_unnamed_addr global i32 200
@x = local_unnamed_addr global i32 25
@global_var_20a8 = constant [97 x i8] c"<rect x=\22%d\22 y=\22%d\22 width=\2250\22 height=\22200\22 fill=\22lightcoral\22 stroke-width=\224\22 stroke=\22pink\22 />\0A\00"
@global_var_2110 = constant [99 x i8] c"<rect x=\22%d\22 y=\22%d\22 width=\22400\22 height=\2240\22 fill=\22saddlebrown\22 stroke-width=\224\22 stroke=\22pink\22 />\0A\0A\00"
@global_var_2178 = constant [99 x i8] c"<rect x=\22%d\22 y=\22%d\22 width=\22%d\22 height=\2235\22 fill=\22lightseagreen\22 stroke-width=\224\22 stroke=\22pink\22 />\0A\00"
@global_var_21db = constant [9 x i8] c"\0A\0A</svg>\00"
@global_var_21e6 = constant [8 x i8] c"out.svg\00"
@global_var_21ee = constant [29 x i8] c"I couldn't open the file :( \00"
@global_var_2210 = constant [89 x i8] c"Enter the number of disks you want , it is not recommended to go for more than 5 tho' : \00"
@global_var_2269 = constant [3 x i8] c"%d\00"
@0 = external global i32
@global_var_401c = local_unnamed_addr global i32 0
@1 = internal constant [2 x i8] c"w\00"
@2 = constant i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i64 0, i64 0)
@global_var_21e4 = constant [2 x i8] c"w\00"

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

define i32 @function_10c0(i32 %c) local_unnamed_addr {
dec_label_pc_10c0:
  %i = call i32 @putchar(i32 %c), !insn.addr !6
  ret i32 %i, !insn.addr !6
}

define i32 @function_10d0(i8* %s) local_unnamed_addr {
dec_label_pc_10d0:
  %i = call i32 @puts(i8* noundef nonnull dereferenceable(1) %s), !insn.addr !7
  ret i32 %i, !insn.addr !7
}

define void @function_10e0() local_unnamed_addr {
dec_label_pc_10e0:
  call void @__stack_chk_fail(), !insn.addr !8
  ret void, !insn.addr !8
}

define i32 @function_10f0(i8* %format, ...) local_unnamed_addr {
dec_label_pc_10f0:
  %i = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) %format), !insn.addr !9
  ret i32 %i, !insn.addr !9
}

define i32 @function_1100(%_IO_FILE* %stream, i8* %format, ...) local_unnamed_addr {
dec_label_pc_1100:
  %i = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stream, i8* %format), !insn.addr !10
  ret i32 %i, !insn.addr !10
}

define %_IO_FILE* @function_1110(i8* %filename, i8* %modes) local_unnamed_addr {
dec_label_pc_1110:
  %i = call %_IO_FILE* @fopen(i8* %filename, i8* %modes), !insn.addr !11
  ret %_IO_FILE* %i, !insn.addr !11
}

define i32 @function_1120(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1120:
  %i = call i32 (i8*, ...) @scanf(i8* %format), !insn.addr !12
  ret i32 %i, !insn.addr !12
}

define i32 @function_1130(i64* %ptr, i32 %size, i32 %n, %_IO_FILE* %s) local_unnamed_addr {
dec_label_pc_1130:
  %i = call i32 @fwrite(i64* %ptr, i32 %size, i32 %n, %_IO_FILE* %s), !insn.addr !13
  ret i32 %i, !insn.addr !13
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1140:
  %stack_var_8 = alloca i8*, align 8
  %i = trunc i64 %arg6 to i32, !insn.addr !14
  %i1 = inttoptr i64 %arg3 to void ()*, !insn.addr !14
  %i2 = call i32 @__libc_start_main(i64 5719, i32 %i, i8** nonnull %stack_var_8, void ()* null, void ()* null, void ()* %i1), !insn.addr !14
  %i3 = call i64 @__asm_hlt(), !insn.addr !15
  unreachable, !insn.addr !15
}

define i64 @deregister_tm_clones() local_unnamed_addr {
dec_label_pc_1170:
  ret i64 ptrtoint (i64* @global_var_4018 to i64), !insn.addr !16
}

define i64 @register_tm_clones() local_unnamed_addr {
dec_label_pc_11a0:
  ret i64 0, !insn.addr !17
}

define i64 @__do_global_dtors_aux() local_unnamed_addr {
dec_label_pc_11e0:
  %i1 = load i8, i8* bitcast (i64* @global_var_4018 to i8*), align 8, !insn.addr !18
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
  store i8 1, i8* bitcast (i64* @global_var_4018 to i8*), align 8, !insn.addr !26
  br label %common.ret

dec_label_pc_1218:                                ; preds = %dec_label_pc_11e0
  br label %common.ret
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1220:
  %i = call i64 @register_tm_clones(), !insn.addr !27
  ret i64 %i, !insn.addr !27
}

define void @initializeaza_caramida(i32* %caramida, i32 %n) local_unnamed_addr {
dec_label_pc_1229:
  %i = icmp sgt i32 %n, 0, !insn.addr !28
  br i1 %i, label %dec_label_pc_1241.lr.ph, label %dec_label_pc_1267, !insn.addr !28

dec_label_pc_1241.lr.ph:                          ; preds = %dec_label_pc_1229
  %i1 = ptrtoint i32* %caramida to i64, !insn.addr !29
  %wide.trip.count = zext i32 %n to i64
  br label %dec_label_pc_1241

dec_label_pc_1241:                                ; preds = %dec_label_pc_1241, %dec_label_pc_1241.lr.ph
  %indvars.iv.reg2mem.0 = phi i64 [ 0, %dec_label_pc_1241.lr.ph ], [ %indvars.iv.next, %dec_label_pc_1241 ]
  %i2 = shl i64 %indvars.iv.reg2mem.0, 2
  %i3 = add i64 %i2, %i1, !insn.addr !30
  %i4 = inttoptr i64 %i3 to i32*, !insn.addr !31
  store i32 0, i32* %i4, align 4, !insn.addr !31
  %indvars.iv.next = add nuw nsw i64 %indvars.iv.reg2mem.0, 1
  %exitcond = icmp eq i64 %indvars.iv.next, %wide.trip.count
  br i1 %exitcond, label %dec_label_pc_1267.loopexit, label %dec_label_pc_1241, !insn.addr !28

dec_label_pc_1267.loopexit:                       ; preds = %dec_label_pc_1241
  br label %dec_label_pc_1267

dec_label_pc_1267:                                ; preds = %dec_label_pc_1267.loopexit, %dec_label_pc_1229
  ret void, !insn.addr !32
}

define void @tower_hanoi(i32 %n, i32 %copy_n, i32 %from, i32 %to, i32 %aux, i32* %caramida, %_IO_FILE* %out) local_unnamed_addr {
dec_label_pc_126b:
  %.not = icmp eq i32 %n, 1, !insn.addr !33
  br i1 %.not, label %dec_label_pc_1291, label %dec_label_pc_12cd, !insn.addr !34

dec_label_pc_1291:                                ; preds = %dec_label_pc_126b
  %i = zext i32 %to to i64, !insn.addr !35
  %i1 = zext i32 %from to i64, !insn.addr !36
  %i2 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([22 x i8], [22 x i8]* @global_var_2008, i64 0, i64 0), i64 %i1, i64 %i), !insn.addr !37
  call void @svg_body(%_IO_FILE* %out, i32 %copy_n, i32* %caramida), !insn.addr !38
  store i32 %to, i32* %caramida, align 4, !insn.addr !39
  br label %dec_label_pc_1373, !insn.addr !40

dec_label_pc_12cd:                                ; preds = %dec_label_pc_126b
  %i3 = add i32 %n, -1, !insn.addr !41
  call void @tower_hanoi(i32 %i3, i32 %copy_n, i32 %from, i32 %aux, i32 %to, i32* %caramida, %_IO_FILE* %out), !insn.addr !42
  %i4 = zext i32 %to to i64, !insn.addr !43
  %i5 = zext i32 %from to i64, !insn.addr !44
  %i6 = zext i32 %n to i64, !insn.addr !45
  %i7 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([23 x i8], [23 x i8]* @global_var_201e, i64 0, i64 0), i64 %i6, i64 %i5, i64 %i4), !insn.addr !46
  call void @svg_body(%_IO_FILE* %out, i32 %copy_n, i32* %caramida), !insn.addr !47
  %i8 = sext i32 %n to i64, !insn.addr !48
  %i9 = shl nsw i64 %i8, 2
  %i10 = add nsw i64 %i9, -4, !insn.addr !49
  %i11 = ptrtoint i32* %caramida to i64, !insn.addr !50
  %i12 = add i64 %i10, %i11, !insn.addr !51
  %i13 = inttoptr i64 %i12 to i32*, !insn.addr !52
  store i32 %to, i32* %i13, align 4, !insn.addr !52
  call void @tower_hanoi(i32 %i3, i32 %copy_n, i32 %aux, i32 %to, i32 %from, i32* %caramida, %_IO_FILE* %out), !insn.addr !53
  br label %dec_label_pc_1373, !insn.addr !54

dec_label_pc_1373:                                ; preds = %dec_label_pc_12cd, %dec_label_pc_1291
  ret void, !insn.addr !55
}

define void @svg_first_thing(%_IO_FILE* %out) local_unnamed_addr {
dec_label_pc_1375:
  %i = call i32 @fwrite(i64* bitcast ([105 x i8]* @global_var_2038 to i64*), i32 1, i32 104, %_IO_FILE* %out), !insn.addr !56
  ret void, !insn.addr !57
}

define void @svg_body(%_IO_FILE* %out, i32 %n, i32* %caramida) local_unnamed_addr {
dec_label_pc_13a8:
  %i = load i32, i32* @y, align 4, !insn.addr !58
  %i4 = add i32 %i, -125, !insn.addr !59
  %i5 = zext i32 %i4 to i64, !insn.addr !59
  %i6 = load i32, i32* @x, align 4, !insn.addr !60
  %i7 = add i32 %i6, 25, !insn.addr !61
  %i8 = zext i32 %i7 to i64, !insn.addr !61
  %i9 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([97 x i8], [97 x i8]* @global_var_20a8, i64 0, i64 0), i64 %i8, i64 %i5), !insn.addr !62
  %i10 = load i32, i32* @y, align 4, !insn.addr !63
  %i11 = add i32 %i10, -125, !insn.addr !64
  %i12 = zext i32 %i11 to i64, !insn.addr !64
  %i13 = load i32, i32* @x, align 4, !insn.addr !65
  %i14 = add i32 %i13, 175, !insn.addr !66
  %i15 = zext i32 %i14 to i64, !insn.addr !66
  %i16 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([97 x i8], [97 x i8]* @global_var_20a8, i64 0, i64 0), i64 %i15, i64 %i12), !insn.addr !67
  %i17 = load i32, i32* @y, align 4, !insn.addr !68
  %i18 = add i32 %i17, -125, !insn.addr !69
  %i19 = zext i32 %i18 to i64, !insn.addr !69
  %i20 = load i32, i32* @x, align 4, !insn.addr !70
  %i21 = add i32 %i20, 310, !insn.addr !71
  %i22 = zext i32 %i21 to i64, !insn.addr !71
  %i23 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([97 x i8], [97 x i8]* @global_var_20a8, i64 0, i64 0), i64 %i22, i64 %i19), !insn.addr !72
  %i24 = load i32, i32* @y, align 4, !insn.addr !73
  %i25 = add i32 %i24, 50, !insn.addr !74
  %i26 = zext i32 %i25 to i64, !insn.addr !74
  %i27 = load i32, i32* @x, align 4, !insn.addr !75
  %i28 = zext i32 %i27 to i64, !insn.addr !75
  %i29 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2110, i64 0, i64 0), i64 %i28, i64 %i26), !insn.addr !76
  %storemerge3 = add i32 %n, -1
  %i30 = icmp sgt i32 %storemerge3, -1
  br i1 %i30, label %dec_label_pc_149a.lr.ph, label %dec_label_pc_15cf, !insn.addr !77

dec_label_pc_149a.lr.ph:                          ; preds = %dec_label_pc_13a8
  %i31 = load i32, i32* @y, align 4
  %i32 = ptrtoint i32* %caramida to i64, !insn.addr !78
  br label %dec_label_pc_149a

dec_label_pc_149a:                                ; preds = %dec_label_pc_149a.lr.ph, %dec_label_pc_15bd
  %storemerge9.reg2mem.0 = phi i32 [ %storemerge3, %dec_label_pc_149a.lr.ph ], [ %storemerge, %dec_label_pc_15bd ]
  %stack_var_-16.07.reg2mem.0 = phi i32 [ 0, %dec_label_pc_149a.lr.ph ], [ %i71, %dec_label_pc_15bd ]
  %stack_var_-20.16.reg2mem.0 = phi i32 [ %i31, %dec_label_pc_149a.lr.ph ], [ %stack_var_-20.0.reg2mem.0, %dec_label_pc_15bd ]
  %centrare_-24.15.reg2mem.0 = phi i32 [ %i31, %dec_label_pc_149a.lr.ph ], [ %centrare_-24.0.reg2mem.0, %dec_label_pc_15bd ]
  %copy3_y_-28.14.reg2mem.0 = phi i32 [ %i31, %dec_label_pc_149a.lr.ph ], [ %copy3_y_-28.0.reg2mem.0, %dec_label_pc_15bd ]
  %i33 = sext i32 %storemerge9.reg2mem.0 to i64, !insn.addr !79
  %i34 = shl nsw i64 %i33, 2
  %i35 = add i64 %i34, %i32, !insn.addr !80
  %i36 = inttoptr i64 %i35 to i32*, !insn.addr !81
  %i37 = load i32, i32* %i36, align 4, !insn.addr !81
  switch i32 %i37, label %dec_label_pc_155d [
    i32 0, label %dec_label_pc_14b4
    i32 1, label %dec_label_pc_1516
  ]

dec_label_pc_14b4:                                ; preds = %dec_label_pc_149a
  %i38 = mul i32 %storemerge9.reg2mem.0, 10, !insn.addr !82
  %i39 = add i32 %i38, 50, !insn.addr !83
  %i40 = add i32 %copy3_y_-28.14.reg2mem.0, 12, !insn.addr !84
  %i41 = zext i32 %i40 to i64, !insn.addr !84
  %i42 = load i32, i32* @x, align 4, !insn.addr !85
  %i43 = add i32 %stack_var_-16.07.reg2mem.0, 3, !insn.addr !86
  %i44 = add i32 %i43, %i42, !insn.addr !87
  %i45 = zext i32 %i44 to i64, !insn.addr !87
  %i46 = zext i32 %i39 to i64, !insn.addr !88
  %i47 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2178, i64 0, i64 0), i64 %i45, i64 %i41, i64 %i46), !insn.addr !89
  %i48 = add i32 %copy3_y_-28.14.reg2mem.0, -35, !insn.addr !90
  br label %dec_label_pc_15bd, !insn.addr !91

dec_label_pc_1516:                                ; preds = %dec_label_pc_149a
  %i49 = mul i32 %storemerge9.reg2mem.0, 10, !insn.addr !92
  %i50 = add i32 %i49, 50, !insn.addr !93
  %i51 = add i32 %centrare_-24.15.reg2mem.0, 12, !insn.addr !94
  %i52 = zext i32 %i51 to i64, !insn.addr !94
  %i53 = load i32, i32* @x, align 4, !insn.addr !95
  %i54 = add i32 %stack_var_-16.07.reg2mem.0, 153, !insn.addr !96
  %i55 = add i32 %i54, %i53, !insn.addr !97
  %i56 = zext i32 %i55 to i64, !insn.addr !97
  %i57 = zext i32 %i50 to i64, !insn.addr !98
  %i58 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2178, i64 0, i64 0), i64 %i56, i64 %i52, i64 %i57), !insn.addr !99
  %i59 = add i32 %centrare_-24.15.reg2mem.0, -35, !insn.addr !100
  br label %dec_label_pc_15bd, !insn.addr !101

dec_label_pc_155d:                                ; preds = %dec_label_pc_149a
  %.not3 = icmp eq i32 %i37, 2, !insn.addr !102
  br i1 %.not3, label %dec_label_pc_1578, label %dec_label_pc_15bd, !insn.addr !103

dec_label_pc_1578:                                ; preds = %dec_label_pc_155d
  %i60 = mul i32 %storemerge9.reg2mem.0, 10, !insn.addr !104
  %i61 = add i32 %i60, 50, !insn.addr !105
  %i62 = add i32 %stack_var_-20.16.reg2mem.0, 12, !insn.addr !106
  %i63 = zext i32 %i62 to i64, !insn.addr !106
  %i64 = load i32, i32* @x, align 4, !insn.addr !107
  %i65 = add i32 %stack_var_-16.07.reg2mem.0, 288, !insn.addr !108
  %i66 = add i32 %i65, %i64, !insn.addr !109
  %i67 = zext i32 %i66 to i64, !insn.addr !109
  %i68 = zext i32 %i61 to i64, !insn.addr !110
  %i69 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2178, i64 0, i64 0), i64 %i67, i64 %i63, i64 %i68), !insn.addr !111
  %i70 = add i32 %stack_var_-20.16.reg2mem.0, -35, !insn.addr !112
  br label %dec_label_pc_15bd, !insn.addr !112

dec_label_pc_15bd:                                ; preds = %dec_label_pc_1578, %dec_label_pc_155d, %dec_label_pc_1516, %dec_label_pc_14b4
  %copy3_y_-28.0.reg2mem.0 = phi i32 [ %copy3_y_-28.14.reg2mem.0, %dec_label_pc_1578 ], [ %copy3_y_-28.14.reg2mem.0, %dec_label_pc_155d ], [ %copy3_y_-28.14.reg2mem.0, %dec_label_pc_1516 ], [ %i48, %dec_label_pc_14b4 ]
  %centrare_-24.0.reg2mem.0 = phi i32 [ %centrare_-24.15.reg2mem.0, %dec_label_pc_1578 ], [ %centrare_-24.15.reg2mem.0, %dec_label_pc_155d ], [ %i59, %dec_label_pc_1516 ], [ %centrare_-24.15.reg2mem.0, %dec_label_pc_14b4 ]
  %stack_var_-20.0.reg2mem.0 = phi i32 [ %i70, %dec_label_pc_1578 ], [ %stack_var_-20.16.reg2mem.0, %dec_label_pc_155d ], [ %stack_var_-20.16.reg2mem.0, %dec_label_pc_1516 ], [ %stack_var_-20.16.reg2mem.0, %dec_label_pc_14b4 ]
  %i71 = add i32 %stack_var_-16.07.reg2mem.0, 5, !insn.addr !113
  %storemerge = add i32 %storemerge9.reg2mem.0, -1
  %i72 = icmp sgt i32 %storemerge, -1
  br i1 %i72, label %dec_label_pc_149a, label %dec_label_pc_15cf.loopexit, !insn.addr !77

dec_label_pc_15cf.loopexit:                       ; preds = %dec_label_pc_15bd
  br label %dec_label_pc_15cf

dec_label_pc_15cf:                                ; preds = %dec_label_pc_15cf.loopexit, %dec_label_pc_13a8
  %i73 = load i32, i32* inttoptr (i64 16412 to i32*), align 4, !insn.addr !114
  %i74 = add i32 %i73, 1, !insn.addr !115
  store i32 %i74, i32* @global_var_401c, align 4, !insn.addr !116
  %.not = icmp eq i32 %i73, 3, !insn.addr !117
  br i1 %.not, label %dec_label_pc_15e9, label %dec_label_pc_1610, !insn.addr !118

dec_label_pc_15e9:                                ; preds = %dec_label_pc_15cf
  store i32 25, i32* @x, align 4, !insn.addr !119
  %i75 = load i32, i32* @y, align 4, !insn.addr !120
  %i76 = add i32 %i75, 275, !insn.addr !121
  store i32 %i76, i32* @y, align 4, !insn.addr !122
  store i32 0, i32* @global_var_401c, align 4, !insn.addr !123
  br label %dec_label_pc_1621, !insn.addr !124

dec_label_pc_1610:                                ; preds = %dec_label_pc_15cf
  %i77 = load i32, i32* @x, align 4, !insn.addr !125
  %i78 = add i32 %i77, 495, !insn.addr !126
  store i32 %i78, i32* @x, align 4, !insn.addr !127
  br label %dec_label_pc_1621, !insn.addr !127

dec_label_pc_1621:                                ; preds = %dec_label_pc_1610, %dec_label_pc_15e9
  ret void, !insn.addr !128
}

define void @svg_final(%_IO_FILE* %out) local_unnamed_addr {
dec_label_pc_1624:
  %i = call i32 @fwrite(i64* bitcast ([9 x i8]* @global_var_21db to i64*), i32 1, i32 8, %_IO_FILE* %out), !insn.addr !129
  ret void, !insn.addr !130
}

define i32 @main() local_unnamed_addr {
dec_label_pc_1657:
  %out_-96 = alloca i32*, align 8
  %n_-104 = alloca i32, align 4
  %i = call i64 @__readfsqword(i64 40), !insn.addr !131
  %i1 = call %_IO_FILE* @fopen(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @global_var_21e6, i64 0, i64 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_var_21e4, i64 0, i64 0)), !insn.addr !132
  %.not = icmp eq %_IO_FILE* %i1, null, !insn.addr !133
  br i1 %.not, label %dec_label_pc_16a5, label %dec_label_pc_16be, !insn.addr !134

dec_label_pc_16a5:                                ; preds = %dec_label_pc_1657
  %i2 = call i32 @puts(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([29 x i8], [29 x i8]* @global_var_21ee, i64 0, i64 0)), !insn.addr !135
  br label %dec_label_pc_1820, !insn.addr !136

dec_label_pc_16be:                                ; preds = %dec_label_pc_1657
  %i3 = ptrtoint %_IO_FILE* %i1 to i64, !insn.addr !132
  %i4 = ptrtoint i32* %n_-104 to i64, !insn.addr !137
  %i5 = call i32 (i8*, ...) @printf(i8* noundef nonnull dereferenceable(1) getelementptr inbounds ([89 x i8], [89 x i8]* @global_var_2210, i64 0, i64 0)), !insn.addr !138
  %i6 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_var_2269, i64 0, i64 0), i32** nonnull %out_-96), !insn.addr !139
  %i7 = call i32 @putchar(i32 10), !insn.addr !140
  %i8 = load i32*, i32** %out_-96, align 8
  %i9 = ptrtoint i32* %i8 to i64
  %sext = shl i64 %i9, 32
  %i10 = ashr exact i64 %sext, 30, !insn.addr !141
  %i11 = add nsw i64 %i10, 15, !insn.addr !142
  %i12 = trunc i64 %i9 to i32
  %i13 = and i64 %i11, -16
  %i14 = sub i64 %i4, %i13
  %i15 = inttoptr i64 %i14 to i32*, !insn.addr !143
  call void @initializeaza_caramida(i32* %i15, i32 %i12), !insn.addr !143
  call void @svg_first_thing(%_IO_FILE* nonnull %i1), !insn.addr !144
  %i16 = load i32*, i32** %out_-96, align 8
  %i17 = ptrtoint i32* %i16 to i64
  %i18 = trunc i64 %i17 to i32, !insn.addr !145
  %i19 = add i64 %i14, -16, !insn.addr !146
  %i20 = inttoptr i64 %i19 to i64*, !insn.addr !146
  store i64 %i3, i64* %i20, align 8, !insn.addr !146
  call void @tower_hanoi(i32 %i18, i32 %i18, i32 0, i32 2, i32 1, i32* %i15, %_IO_FILE* bitcast (i32* @0 to %_IO_FILE*)), !insn.addr !147
  call void @svg_body(%_IO_FILE* nonnull %i1, i32 %i12, i32* %i15), !insn.addr !148
  call void @svg_final(%_IO_FILE* nonnull %i1), !insn.addr !149
  br label %dec_label_pc_1820, !insn.addr !150

dec_label_pc_1820:                                ; preds = %dec_label_pc_16be, %dec_label_pc_16a5
  %i21 = call i64 @__readfsqword(i64 40), !insn.addr !151
  %i22 = icmp eq i64 %i, %i21, !insn.addr !151
  br i1 %i22, label %dec_label_pc_1837, label %dec_label_pc_1832, !insn.addr !152

dec_label_pc_1832:                                ; preds = %dec_label_pc_1820
  call void @__stack_chk_fail(), !insn.addr !153
  br label %dec_label_pc_1837, !insn.addr !153

dec_label_pc_1837:                                ; preds = %dec_label_pc_1832, %dec_label_pc_1820
  %rax.0.reg2mem.0 = phi i32 [ 0, %dec_label_pc_1820 ], [ ptrtoint (i32* @0 to i32), %dec_label_pc_1832 ]
  ret i32 %rax.0.reg2mem.0, !insn.addr !154
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1848:
  ret i64 undef, !insn.addr !155
}

declare i32 @putchar(i32) local_unnamed_addr

declare i32 @puts(i8*) local_unnamed_addr

declare void @__stack_chk_fail() local_unnamed_addr

declare i32 @printf(i8*, ...) local_unnamed_addr

declare i32 @fprintf(%_IO_FILE*, i8*, ...) local_unnamed_addr

declare %_IO_FILE* @fopen(i8*, i8*) local_unnamed_addr

declare i32 @scanf(i8*, ...) local_unnamed_addr

declare i32 @fwrite(i64*, i32, i32, %_IO_FILE*) local_unnamed_addr

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
!28 = !{i64 4709}
!29 = !{i64 4686}
!30 = !{i64 4690}
!31 = !{i64 4693}
!32 = !{i64 4714}
!33 = !{i64 4747}
!34 = !{i64 4751}
!35 = !{i64 4753}
!36 = !{i64 4759}
!37 = !{i64 4776}
!38 = !{i64 4794}
!39 = !{i64 4806}
!40 = !{i64 4808}
!41 = !{i64 4816}
!42 = !{i64 4850}
!43 = !{i64 4859}
!44 = !{i64 4862}
!45 = !{i64 4868}
!46 = !{i64 4885}
!47 = !{i64 4903}
!48 = !{i64 4911}
!49 = !{i64 4917}
!50 = !{i64 4921}
!51 = !{i64 4925}
!52 = !{i64 4931}
!53 = !{i64 4970}
!54 = !{i64 4975}
!55 = !{i64 4980}
!56 = !{i64 5024}
!57 = !{i64 5031}
!58 = !{i64 5055}
!59 = !{i64 5061}
!60 = !{i64 5064}
!61 = !{i64 5070}
!62 = !{i64 5092}
!63 = !{i64 5097}
!64 = !{i64 5103}
!65 = !{i64 5106}
!66 = !{i64 5112}
!67 = !{i64 5137}
!68 = !{i64 5142}
!69 = !{i64 5148}
!70 = !{i64 5151}
!71 = !{i64 5157}
!72 = !{i64 5182}
!73 = !{i64 5187}
!74 = !{i64 5193}
!75 = !{i64 5196}
!76 = !{i64 5221}
!77 = !{i64 5577}
!78 = !{i64 5287}
!79 = !{i64 5277}
!80 = !{i64 5291}
!81 = !{i64 5294}
!82 = !{i64 5310}
!83 = !{i64 5312}
!84 = !{i64 5318}
!85 = !{i64 5321}
!86 = !{i64 5327}
!87 = !{i64 5333}
!88 = !{i64 5339}
!89 = !{i64 5357}
!90 = !{i64 5362}
!91 = !{i64 5366}
!92 = !{i64 5408}
!93 = !{i64 5410}
!94 = !{i64 5416}
!95 = !{i64 5419}
!96 = !{i64 5425}
!97 = !{i64 5434}
!98 = !{i64 5440}
!99 = !{i64 5458}
!100 = !{i64 5463}
!101 = !{i64 5467}
!102 = !{i64 5491}
!103 = !{i64 5494}
!104 = !{i64 5506}
!105 = !{i64 5508}
!106 = !{i64 5514}
!107 = !{i64 5517}
!108 = !{i64 5523}
!109 = !{i64 5532}
!110 = !{i64 5538}
!111 = !{i64 5556}
!112 = !{i64 5561}
!113 = !{i64 5565}
!114 = !{i64 5583}
!115 = !{i64 5589}
!116 = !{i64 5592}
!117 = !{i64 5604}
!118 = !{i64 5607}
!119 = !{i64 5609}
!120 = !{i64 5619}
!121 = !{i64 5625}
!122 = !{i64 5630}
!123 = !{i64 5636}
!124 = !{i64 5646}
!125 = !{i64 5648}
!126 = !{i64 5654}
!127 = !{i64 5659}
!128 = !{i64 5667}
!129 = !{i64 5711}
!130 = !{i64 5718}
!131 = !{i64 5740}
!132 = !{i64 5781}
!133 = !{i64 5790}
!134 = !{i64 5795}
!135 = !{i64 5807}
!136 = !{i64 5817}
!137 = !{i64 5736}
!138 = !{i64 5837}
!139 = !{i64 5864}
!140 = !{i64 5874}
!141 = !{i64 5925}
!142 = !{i64 5942}
!143 = !{i64 6074}
!144 = !{i64 6086}
!145 = !{i64 6091}
!146 = !{i64 6105}
!147 = !{i64 6129}
!148 = !{i64 6154}
!149 = !{i64 6166}
!150 = !{i64 6171}
!151 = !{i64 6183}
!152 = !{i64 6192}
!153 = !{i64 6194}
!154 = !{i64 6213}
!155 = !{i64 6228}
