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

define void @function_10b0(i64* %d) local_unnamed_addr {
dec_label_pc_10b0:
  call void @__cxa_finalize(i64* %d), !insn.addr !6
  ret void, !insn.addr !6
}

define i32 @function_10c0(i32 %c) local_unnamed_addr {
dec_label_pc_10c0:
  %0 = call i32 @putchar(i32 %c), !insn.addr !7
  ret i32 %0, !insn.addr !7
}

define i32 @function_10d0(i8* %s) local_unnamed_addr {
dec_label_pc_10d0:
  %0 = call i32 @puts(i8* %s), !insn.addr !8
  ret i32 %0, !insn.addr !8
}

define void @function_10e0() local_unnamed_addr {
dec_label_pc_10e0:
  call void @__stack_chk_fail(), !insn.addr !9
  ret void, !insn.addr !9
}

define i32 @function_10f0(i8* %format, ...) local_unnamed_addr {
dec_label_pc_10f0:
  %0 = call i32 (i8*, ...) @printf(i8* %format), !insn.addr !10
  ret i32 %0, !insn.addr !10
}

define i32 @function_1100(%_IO_FILE* %stream, i8* %format, ...) local_unnamed_addr {
dec_label_pc_1100:
  %0 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %stream, i8* %format), !insn.addr !11
  ret i32 %0, !insn.addr !11
}

define %_IO_FILE* @function_1110(i8* %filename, i8* %modes) local_unnamed_addr {
dec_label_pc_1110:
  %0 = call %_IO_FILE* @fopen(i8* %filename, i8* %modes), !insn.addr !12
  ret %_IO_FILE* %0, !insn.addr !12
}

define i32 @function_1120(i8* %format, ...) local_unnamed_addr {
dec_label_pc_1120:
  %0 = call i32 (i8*, ...) @scanf(i8* %format), !insn.addr !13
  ret i32 %0, !insn.addr !13
}

define i32 @function_1130(i64* %ptr, i32 %size, i32 %n, %_IO_FILE* %s) local_unnamed_addr {
dec_label_pc_1130:
  %0 = call i32 @fwrite(i64* %ptr, i32 %size, i32 %n, %_IO_FILE* %s), !insn.addr !14
  ret i32 %0, !insn.addr !14
}

define i64 @_start(i64 %arg1, i64 %arg2, i64 %arg3, i64 %arg4, i64 %arg5, i64 %arg6) local_unnamed_addr {
dec_label_pc_1140:
  %stack_var_8 = alloca i64, align 8
  %0 = trunc i64 %arg6 to i32, !insn.addr !15
  %1 = bitcast i64* %stack_var_8 to i8**, !insn.addr !15
  %2 = inttoptr i64 %arg3 to void ()*, !insn.addr !15
  %3 = call i32 @__libc_start_main(i64 5719, i32 %0, i8** nonnull %1, void ()* null, void ()* null, void ()* %2), !insn.addr !15
  %4 = call i64 @__asm_hlt(), !insn.addr !16
  unreachable, !insn.addr !16
}

define i64 @deregister_tm_clones() local_unnamed_addr {
dec_label_pc_1170:
  ret i64 ptrtoint (i64* @global_var_4018 to i64), !insn.addr !17
}

define i64 @register_tm_clones() local_unnamed_addr {
dec_label_pc_11a0:
  ret i64 0, !insn.addr !18
}

define i64 @__do_global_dtors_aux() local_unnamed_addr {
dec_label_pc_11e0:
  %0 = alloca i64
  %1 = load i64, i64* %0
  %2 = load i8, i8* bitcast (i64* @global_var_4018 to i8*), align 8, !insn.addr !19
  %3 = icmp eq i8 %2, 0, !insn.addr !19
  %4 = icmp eq i1 %3, false, !insn.addr !20
  br i1 %4, label %dec_label_pc_1218, label %dec_label_pc_11ed, !insn.addr !20

dec_label_pc_11ed:                                ; preds = %dec_label_pc_11e0
  %5 = load i64, i64* inttoptr (i64 16376 to i64*), align 8, !insn.addr !21
  %6 = icmp eq i64 %5, 0, !insn.addr !21
  br i1 %6, label %dec_label_pc_1207, label %dec_label_pc_11fb, !insn.addr !22

dec_label_pc_11fb:                                ; preds = %dec_label_pc_11ed
  %7 = load i64, i64* inttoptr (i64 16392 to i64*), align 8, !insn.addr !23
  %8 = inttoptr i64 %7 to i64*, !insn.addr !24
  call void @__cxa_finalize(i64* %8), !insn.addr !24
  br label %dec_label_pc_1207, !insn.addr !24

dec_label_pc_1207:                                ; preds = %dec_label_pc_11fb, %dec_label_pc_11ed
  %9 = call i64 @deregister_tm_clones(), !insn.addr !25
  store i8 1, i8* bitcast (i64* @global_var_4018 to i8*), align 8, !insn.addr !26
  ret i64 %9, !insn.addr !27

dec_label_pc_1218:                                ; preds = %dec_label_pc_11e0
  ret i64 %1, !insn.addr !28
}

define i64 @frame_dummy() local_unnamed_addr {
dec_label_pc_1220:
  %0 = call i64 @register_tm_clones(), !insn.addr !29
  ret i64 %0, !insn.addr !29
}

define void @initializeaza_caramida(i32* %caramida, i32 %n) local_unnamed_addr {
dec_label_pc_1229:
  %indvars.iv.reg2mem = alloca i64, !insn.addr !30
  %0 = icmp sgt i32 %n, 0, !insn.addr !31
  br i1 %0, label %dec_label_pc_1241.lr.ph, label %dec_label_pc_1267, !insn.addr !31

dec_label_pc_1241.lr.ph:                          ; preds = %dec_label_pc_1229
  %1 = ptrtoint i32* %caramida to i64, !insn.addr !32
  %wide.trip.count = zext i32 %n to i64
  store i64 0, i64* %indvars.iv.reg2mem
  br label %dec_label_pc_1241

dec_label_pc_1241:                                ; preds = %dec_label_pc_1241, %dec_label_pc_1241.lr.ph
  %indvars.iv.reload = load i64, i64* %indvars.iv.reg2mem
  %2 = mul i64 %indvars.iv.reload, 4, !insn.addr !33
  %3 = add i64 %2, %1, !insn.addr !34
  %4 = inttoptr i64 %3 to i32*, !insn.addr !35
  store i32 0, i32* %4, align 4, !insn.addr !35
  %indvars.iv.next = add nuw nsw i64 %indvars.iv.reload, 1
  %exitcond = icmp eq i64 %indvars.iv.next, %wide.trip.count
  store i64 %indvars.iv.next, i64* %indvars.iv.reg2mem, !insn.addr !31
  br i1 %exitcond, label %dec_label_pc_1267, label %dec_label_pc_1241, !insn.addr !31

dec_label_pc_1267:                                ; preds = %dec_label_pc_1241, %dec_label_pc_1229
  ret void, !insn.addr !36

; uselistorder directives
  uselistorder i64* %indvars.iv.reg2mem, { 1, 0, 2 }
}

define void @tower_hanoi(i32 %n, i32 %copy_n, i32 %from, i32 %to, i32 %aux, i32* %caramida, %_IO_FILE* %out) local_unnamed_addr {
dec_label_pc_126b:
  %stack_var_8 = alloca %_IO_FILE*, align 8
  store %_IO_FILE* %out, %_IO_FILE** %stack_var_8, align 8
  %0 = icmp eq i32 %n, 1, !insn.addr !37
  %1 = icmp eq i1 %0, false, !insn.addr !38
  br i1 %1, label %dec_label_pc_12cd, label %dec_label_pc_1291, !insn.addr !38

dec_label_pc_1291:                                ; preds = %dec_label_pc_126b
  %2 = zext i32 %to to i64, !insn.addr !39
  %3 = zext i32 %from to i64, !insn.addr !40
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @global_var_2008, i64 0, i64 0), i64 %3, i64 %2), !insn.addr !41
  call void @svg_body(%_IO_FILE* %out, i32 %copy_n, i32* %caramida), !insn.addr !42
  store i32 %to, i32* %caramida, align 4, !insn.addr !43
  br label %dec_label_pc_1373, !insn.addr !44

dec_label_pc_12cd:                                ; preds = %dec_label_pc_126b
  %5 = add i32 %n, -1, !insn.addr !45
  call void @tower_hanoi(i32 %5, i32 %copy_n, i32 %from, i32 %aux, i32 %to, i32* %caramida, %_IO_FILE* %out), !insn.addr !46
  %6 = zext i32 %to to i64, !insn.addr !47
  %7 = zext i32 %from to i64, !insn.addr !48
  %8 = zext i32 %n to i64, !insn.addr !49
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @global_var_201e, i64 0, i64 0), i64 %8, i64 %7, i64 %6), !insn.addr !50
  call void @svg_body(%_IO_FILE* %out, i32 %copy_n, i32* %caramida), !insn.addr !51
  %10 = sext i32 %n to i64, !insn.addr !52
  %11 = mul i64 %10, 4, !insn.addr !53
  %12 = add nsw i64 %11, -4, !insn.addr !54
  %13 = ptrtoint i32* %caramida to i64, !insn.addr !55
  %14 = add i64 %12, %13, !insn.addr !56
  %15 = inttoptr i64 %14 to i32*, !insn.addr !57
  store i32 %to, i32* %15, align 4, !insn.addr !57
  %16 = load %_IO_FILE*, %_IO_FILE** %stack_var_8, align 8
  call void @tower_hanoi(i32 %5, i32 %copy_n, i32 %aux, i32 %to, i32 %from, i32* %caramida, %_IO_FILE* %16), !insn.addr !58
  br label %dec_label_pc_1373, !insn.addr !59

dec_label_pc_1373:                                ; preds = %dec_label_pc_12cd, %dec_label_pc_1291
  ret void, !insn.addr !60

; uselistorder directives
  uselistorder i32* %caramida, { 2, 3, 4, 5, 1, 0 }
  uselistorder i32 %to, { 2, 3, 4, 5, 0, 1 }
  uselistorder i32 %from, { 1, 2, 3, 0 }
  uselistorder i32 %copy_n, { 1, 2, 3, 0 }
}

define void @svg_first_thing(%_IO_FILE* %out) local_unnamed_addr {
dec_label_pc_1375:
  %0 = call i32 @fwrite(i64* bitcast ([105 x i8]* @global_var_2038 to i64*), i32 1, i32 104, %_IO_FILE* %out), !insn.addr !61
  ret void, !insn.addr !62
}

define void @svg_body(%_IO_FILE* %out, i32 %n, i32* %caramida) local_unnamed_addr {
dec_label_pc_13a8:
  %stack_var_-20.0.reg2mem = alloca i32, !insn.addr !63
  %centrare_-24.0.reg2mem = alloca i32, !insn.addr !63
  %copy3_y_-28.0.reg2mem = alloca i32, !insn.addr !63
  %copy3_y_-28.14.reg2mem = alloca i32, !insn.addr !63
  %centrare_-24.15.reg2mem = alloca i32, !insn.addr !63
  %stack_var_-20.16.reg2mem = alloca i32, !insn.addr !63
  %stack_var_-16.07.reg2mem = alloca i32, !insn.addr !63
  %storemerge9.reg2mem = alloca i32, !insn.addr !63
  %0 = load i32, i32* @y, align 4, !insn.addr !64
  %1 = add i32 %0, -125, !insn.addr !65
  %2 = zext i32 %1 to i64, !insn.addr !65
  %3 = load i32, i32* @x, align 4, !insn.addr !66
  %4 = add i32 %3, 25, !insn.addr !67
  %5 = zext i32 %4 to i64, !insn.addr !67
  %6 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([97 x i8], [97 x i8]* @global_var_20a8, i64 0, i64 0), i64 %5, i64 %2), !insn.addr !68
  %7 = load i32, i32* @y, align 4, !insn.addr !69
  %8 = add i32 %7, -125, !insn.addr !70
  %9 = zext i32 %8 to i64, !insn.addr !70
  %10 = load i32, i32* @x, align 4, !insn.addr !71
  %11 = add i32 %10, 175, !insn.addr !72
  %12 = zext i32 %11 to i64, !insn.addr !72
  %13 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([97 x i8], [97 x i8]* @global_var_20a8, i64 0, i64 0), i64 %12, i64 %9), !insn.addr !73
  %14 = load i32, i32* @y, align 4, !insn.addr !74
  %15 = add i32 %14, -125, !insn.addr !75
  %16 = zext i32 %15 to i64, !insn.addr !75
  %17 = load i32, i32* @x, align 4, !insn.addr !76
  %18 = add i32 %17, 310, !insn.addr !77
  %19 = zext i32 %18 to i64, !insn.addr !77
  %20 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([97 x i8], [97 x i8]* @global_var_20a8, i64 0, i64 0), i64 %19, i64 %16), !insn.addr !78
  %21 = load i32, i32* @y, align 4, !insn.addr !79
  %22 = add i32 %21, 50, !insn.addr !80
  %23 = zext i32 %22 to i64, !insn.addr !80
  %24 = load i32, i32* @x, align 4, !insn.addr !81
  %25 = zext i32 %24 to i64, !insn.addr !81
  %26 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2110, i64 0, i64 0), i64 %25, i64 %23), !insn.addr !82
  %storemerge3 = add i32 %n, -1
  %27 = icmp slt i32 %storemerge3, 0, !insn.addr !83
  %28 = icmp eq i1 %27, false, !insn.addr !84
  br i1 %28, label %dec_label_pc_149a.lr.ph, label %dec_label_pc_15cf, !insn.addr !84

dec_label_pc_149a.lr.ph:                          ; preds = %dec_label_pc_13a8
  %29 = load i32, i32* @y, align 4
  %30 = ptrtoint i32* %caramida to i64, !insn.addr !85
  store i32 %storemerge3, i32* %storemerge9.reg2mem
  store i32 0, i32* %stack_var_-16.07.reg2mem
  store i32 %29, i32* %stack_var_-20.16.reg2mem
  store i32 %29, i32* %centrare_-24.15.reg2mem
  store i32 %29, i32* %copy3_y_-28.14.reg2mem
  br label %dec_label_pc_149a

dec_label_pc_149a:                                ; preds = %dec_label_pc_149a.lr.ph, %dec_label_pc_15bd
  %copy3_y_-28.14.reload = load i32, i32* %copy3_y_-28.14.reg2mem
  %centrare_-24.15.reload = load i32, i32* %centrare_-24.15.reg2mem
  %stack_var_-20.16.reload = load i32, i32* %stack_var_-20.16.reg2mem
  %stack_var_-16.07.reload = load i32, i32* %stack_var_-16.07.reg2mem
  %storemerge9.reload = load i32, i32* %storemerge9.reg2mem
  %31 = sext i32 %storemerge9.reload to i64, !insn.addr !86
  %32 = mul i64 %31, 4, !insn.addr !87
  %33 = add i64 %32, %30, !insn.addr !88
  %34 = inttoptr i64 %33 to i32*, !insn.addr !89
  %35 = load i32, i32* %34, align 4, !insn.addr !89
  %36 = icmp eq i32 %35, 0, !insn.addr !90
  %37 = icmp eq i1 %36, false, !insn.addr !91
  br i1 %37, label %dec_label_pc_14fb, label %dec_label_pc_14b4, !insn.addr !91

dec_label_pc_14b4:                                ; preds = %dec_label_pc_149a
  %38 = mul i32 %storemerge9.reload, 10, !insn.addr !92
  %39 = add i32 %38, 50, !insn.addr !93
  %40 = add i32 %copy3_y_-28.14.reload, 12, !insn.addr !94
  %41 = zext i32 %40 to i64, !insn.addr !94
  %42 = load i32, i32* @x, align 4, !insn.addr !95
  %43 = add i32 %stack_var_-16.07.reload, 3, !insn.addr !96
  %44 = add i32 %43, %42, !insn.addr !97
  %45 = zext i32 %44 to i64, !insn.addr !97
  %46 = zext i32 %39 to i64, !insn.addr !98
  %47 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2178, i64 0, i64 0), i64 %45, i64 %41, i64 %46), !insn.addr !99
  %48 = add i32 %copy3_y_-28.14.reload, -35, !insn.addr !100
  store i32 %48, i32* %copy3_y_-28.0.reg2mem, !insn.addr !101
  store i32 %centrare_-24.15.reload, i32* %centrare_-24.0.reg2mem, !insn.addr !101
  store i32 %stack_var_-20.16.reload, i32* %stack_var_-20.0.reg2mem, !insn.addr !101
  br label %dec_label_pc_15bd, !insn.addr !101

dec_label_pc_14fb:                                ; preds = %dec_label_pc_149a
  %49 = icmp eq i32 %35, 1, !insn.addr !102
  %50 = icmp eq i1 %49, false, !insn.addr !103
  br i1 %50, label %dec_label_pc_155d, label %dec_label_pc_1516, !insn.addr !103

dec_label_pc_1516:                                ; preds = %dec_label_pc_14fb
  %51 = mul i32 %storemerge9.reload, 10, !insn.addr !104
  %52 = add i32 %51, 50, !insn.addr !105
  %53 = add i32 %centrare_-24.15.reload, 12, !insn.addr !106
  %54 = zext i32 %53 to i64, !insn.addr !106
  %55 = load i32, i32* @x, align 4, !insn.addr !107
  %56 = add i32 %stack_var_-16.07.reload, 153, !insn.addr !108
  %57 = add i32 %56, %55, !insn.addr !109
  %58 = zext i32 %57 to i64, !insn.addr !109
  %59 = zext i32 %52 to i64, !insn.addr !110
  %60 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2178, i64 0, i64 0), i64 %58, i64 %54, i64 %59), !insn.addr !111
  %61 = add i32 %centrare_-24.15.reload, -35, !insn.addr !112
  store i32 %copy3_y_-28.14.reload, i32* %copy3_y_-28.0.reg2mem, !insn.addr !113
  store i32 %61, i32* %centrare_-24.0.reg2mem, !insn.addr !113
  store i32 %stack_var_-20.16.reload, i32* %stack_var_-20.0.reg2mem, !insn.addr !113
  br label %dec_label_pc_15bd, !insn.addr !113

dec_label_pc_155d:                                ; preds = %dec_label_pc_14fb
  %62 = icmp eq i32 %35, 2, !insn.addr !114
  %63 = icmp eq i1 %62, false, !insn.addr !115
  store i32 %copy3_y_-28.14.reload, i32* %copy3_y_-28.0.reg2mem, !insn.addr !115
  store i32 %centrare_-24.15.reload, i32* %centrare_-24.0.reg2mem, !insn.addr !115
  store i32 %stack_var_-20.16.reload, i32* %stack_var_-20.0.reg2mem, !insn.addr !115
  br i1 %63, label %dec_label_pc_15bd, label %dec_label_pc_1578, !insn.addr !115

dec_label_pc_1578:                                ; preds = %dec_label_pc_155d
  %64 = mul i32 %storemerge9.reload, 10, !insn.addr !116
  %65 = add i32 %64, 50, !insn.addr !117
  %66 = add i32 %stack_var_-20.16.reload, 12, !insn.addr !118
  %67 = zext i32 %66 to i64, !insn.addr !118
  %68 = load i32, i32* @x, align 4, !insn.addr !119
  %69 = add i32 %stack_var_-16.07.reload, 288, !insn.addr !120
  %70 = add i32 %69, %68, !insn.addr !121
  %71 = zext i32 %70 to i64, !insn.addr !121
  %72 = zext i32 %65 to i64, !insn.addr !122
  %73 = call i32 (%_IO_FILE*, i8*, ...) @fprintf(%_IO_FILE* %out, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @global_var_2178, i64 0, i64 0), i64 %71, i64 %67, i64 %72), !insn.addr !123
  %74 = add i32 %stack_var_-20.16.reload, -35, !insn.addr !124
  store i32 %copy3_y_-28.14.reload, i32* %copy3_y_-28.0.reg2mem, !insn.addr !124
  store i32 %centrare_-24.15.reload, i32* %centrare_-24.0.reg2mem, !insn.addr !124
  store i32 %74, i32* %stack_var_-20.0.reg2mem, !insn.addr !124
  br label %dec_label_pc_15bd, !insn.addr !124

dec_label_pc_15bd:                                ; preds = %dec_label_pc_1578, %dec_label_pc_155d, %dec_label_pc_1516, %dec_label_pc_14b4
  %stack_var_-20.0.reload = load i32, i32* %stack_var_-20.0.reg2mem
  %centrare_-24.0.reload = load i32, i32* %centrare_-24.0.reg2mem
  %copy3_y_-28.0.reload = load i32, i32* %copy3_y_-28.0.reg2mem
  %75 = add i32 %stack_var_-16.07.reload, 5, !insn.addr !125
  %storemerge = add i32 %storemerge9.reload, -1
  %76 = icmp slt i32 %storemerge, 0, !insn.addr !83
  %77 = icmp eq i1 %76, false, !insn.addr !84
  store i32 %storemerge, i32* %storemerge9.reg2mem, !insn.addr !84
  store i32 %75, i32* %stack_var_-16.07.reg2mem, !insn.addr !84
  store i32 %stack_var_-20.0.reload, i32* %stack_var_-20.16.reg2mem, !insn.addr !84
  store i32 %centrare_-24.0.reload, i32* %centrare_-24.15.reg2mem, !insn.addr !84
  store i32 %copy3_y_-28.0.reload, i32* %copy3_y_-28.14.reg2mem, !insn.addr !84
  br i1 %77, label %dec_label_pc_149a, label %dec_label_pc_15cf, !insn.addr !84

dec_label_pc_15cf:                                ; preds = %dec_label_pc_15bd, %dec_label_pc_13a8
  %78 = load i32, i32* inttoptr (i64 16412 to i32*), align 4, !insn.addr !126
  %79 = add i32 %78, 1, !insn.addr !127
  store i32 %79, i32* @global_var_401c, align 4, !insn.addr !128
  %80 = icmp eq i32 %78, 3, !insn.addr !129
  %81 = icmp eq i1 %80, false, !insn.addr !130
  br i1 %81, label %dec_label_pc_1610, label %dec_label_pc_15e9, !insn.addr !130

dec_label_pc_15e9:                                ; preds = %dec_label_pc_15cf
  store i32 25, i32* @x, align 4, !insn.addr !131
  %82 = load i32, i32* @y, align 4, !insn.addr !132
  %83 = add i32 %82, 275, !insn.addr !133
  store i32 %83, i32* @y, align 4, !insn.addr !134
  store i32 0, i32* @global_var_401c, align 4, !insn.addr !135
  br label %dec_label_pc_1621, !insn.addr !136

dec_label_pc_1610:                                ; preds = %dec_label_pc_15cf
  %84 = load i32, i32* @x, align 4, !insn.addr !137
  %85 = add i32 %84, 495, !insn.addr !138
  store i32 %85, i32* @x, align 4, !insn.addr !139
  br label %dec_label_pc_1621, !insn.addr !139

dec_label_pc_1621:                                ; preds = %dec_label_pc_1610, %dec_label_pc_15e9
  ret void, !insn.addr !140

; uselistorder directives
  uselistorder i32 %storemerge9.reload, { 4, 0, 1, 2, 3 }
  uselistorder i32 %stack_var_-16.07.reload, { 3, 0, 1, 2 }
  uselistorder i32 %stack_var_-20.16.reload, { 3, 4, 2, 1, 0 }
  uselistorder i32 %centrare_-24.15.reload, { 1, 2, 3, 4, 0 }
  uselistorder i32 %copy3_y_-28.14.reload, { 1, 2, 0, 3, 4 }
  uselistorder i32* %storemerge9.reg2mem, { 1, 0, 2 }
  uselistorder i32* %stack_var_-16.07.reg2mem, { 1, 0, 2 }
  uselistorder i32* %stack_var_-20.16.reg2mem, { 1, 0, 2 }
  uselistorder i32* %centrare_-24.15.reg2mem, { 1, 0, 2 }
  uselistorder i32* %copy3_y_-28.14.reg2mem, { 1, 0, 2 }
  uselistorder i32* %copy3_y_-28.0.reg2mem, { 0, 3, 4, 2, 1 }
  uselistorder i32* %centrare_-24.0.reg2mem, { 0, 3, 4, 2, 1 }
  uselistorder i32* %stack_var_-20.0.reg2mem, { 0, 3, 4, 2, 1 }
  uselistorder i32* @global_var_401c, { 1, 0 }
  uselistorder i32 3, { 1, 0 }
  uselistorder i32 -1, { 1, 0, 2 }
  uselistorder i32 (%_IO_FILE*, i8*, ...)* @fprintf, { 4, 5, 6, 3, 2, 1, 0, 7 }
  uselistorder i32 25, { 2, 0, 1 }
  uselistorder %_IO_FILE* %out, { 2, 1, 0, 3, 4, 5, 6 }
  uselistorder label %dec_label_pc_149a, { 1, 0 }
}

define void @svg_final(%_IO_FILE* %out) local_unnamed_addr {
dec_label_pc_1624:
  %0 = call i32 @fwrite(i64* bitcast ([9 x i8]* @global_var_21db to i64*), i32 1, i32 8, %_IO_FILE* %out), !insn.addr !141
  ret void, !insn.addr !142
}

define i32 @main() local_unnamed_addr {
dec_label_pc_1657:
  %rax.0.reg2mem = alloca i32, !insn.addr !143
  %out_-96 = alloca i32*, align 8
  %n_-104 = alloca i32, align 4
  %0 = call i64 @__readfsqword(i64 40), !insn.addr !144
  %1 = call %_IO_FILE* @fopen(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @global_var_21e6, i64 0, i64 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @global_var_21e4, i64 0, i64 0)), !insn.addr !145
  %2 = icmp eq %_IO_FILE* %1, null, !insn.addr !146
  %3 = icmp eq i1 %2, false, !insn.addr !147
  br i1 %3, label %dec_label_pc_16be, label %dec_label_pc_16a5, !insn.addr !147

dec_label_pc_16a5:                                ; preds = %dec_label_pc_1657
  %4 = call i32 @puts(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @global_var_21ee, i64 0, i64 0)), !insn.addr !148
  br label %dec_label_pc_1820, !insn.addr !149

dec_label_pc_16be:                                ; preds = %dec_label_pc_1657
  %5 = ptrtoint %_IO_FILE* %1 to i64, !insn.addr !145
  %6 = ptrtoint i32* %n_-104 to i64, !insn.addr !150
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([89 x i8], [89 x i8]* @global_var_2210, i64 0, i64 0)), !insn.addr !151
  %8 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @global_var_2269, i64 0, i64 0), i32** nonnull %out_-96), !insn.addr !152
  %9 = call i32 @putchar(i32 10), !insn.addr !153
  %10 = load i32*, i32** %out_-96, align 8
  %11 = ptrtoint i32* %10 to i64
  %sext = mul i64 %11, 4294967296
  %12 = ashr exact i64 %sext, 30, !insn.addr !154
  %13 = add nsw i64 %12, 15, !insn.addr !155
  %14 = udiv i64 %13, 16
  %15 = mul i64 %14, 16
  %16 = and i64 %15, -4096, !insn.addr !156
  %17 = sub i64 %6, %16, !insn.addr !157
  %18 = trunc i64 %11 to i32
  %19 = and i64 %15, 4080, !insn.addr !158
  %20 = sub i64 %17, %19, !insn.addr !159
  %21 = inttoptr i64 %20 to i32*, !insn.addr !160
  call void @initializeaza_caramida(i32* %21, i32 %18), !insn.addr !160
  call void @svg_first_thing(%_IO_FILE* %1), !insn.addr !161
  %22 = load i32*, i32** %out_-96, align 8
  %23 = ptrtoint i32* %22 to i64
  %24 = trunc i64 %23 to i32, !insn.addr !162
  %25 = add i64 %20, -16, !insn.addr !163
  %26 = inttoptr i64 %25 to i64*, !insn.addr !163
  store i64 %5, i64* %26, align 8, !insn.addr !163
  call void @tower_hanoi(i32 %24, i32 %24, i32 0, i32 2, i32 1, i32* %21, %_IO_FILE* bitcast (i32* @0 to %_IO_FILE*)), !insn.addr !164
  call void @svg_body(%_IO_FILE* %1, i32 %18, i32* %21), !insn.addr !165
  call void @svg_final(%_IO_FILE* %1), !insn.addr !166
  br label %dec_label_pc_1820, !insn.addr !167

dec_label_pc_1820:                                ; preds = %dec_label_pc_16be, %dec_label_pc_16a5
  %27 = call i64 @__readfsqword(i64 40), !insn.addr !168
  %28 = icmp eq i64 %0, %27, !insn.addr !168
  store i32 0, i32* %rax.0.reg2mem, !insn.addr !169
  br i1 %28, label %dec_label_pc_1837, label %dec_label_pc_1832, !insn.addr !169

dec_label_pc_1832:                                ; preds = %dec_label_pc_1820
  call void @__stack_chk_fail(), !insn.addr !170
  store i32 ptrtoint (i32* @0 to i32), i32* %rax.0.reg2mem, !insn.addr !170
  br label %dec_label_pc_1837, !insn.addr !170

dec_label_pc_1837:                                ; preds = %dec_label_pc_1832, %dec_label_pc_1820
  %rax.0.reload = load i32, i32* %rax.0.reg2mem
  ret i32 %rax.0.reload, !insn.addr !171

; uselistorder directives
  uselistorder i32 %24, { 1, 0 }
  uselistorder i64 %20, { 1, 0 }
  uselistorder i32 %18, { 1, 0 }
  uselistorder i64 %15, { 1, 0 }
  uselistorder i64 %11, { 1, 0 }
  uselistorder %_IO_FILE* %1, { 0, 1, 2, 4, 3 }
  uselistorder i32** %out_-96, { 1, 2, 0 }
  uselistorder void (%_IO_FILE*, i32, i32*)* @svg_body, { 2, 1, 0 }
  uselistorder void (i32, i32, i32, i32, i32, i32*, %_IO_FILE*)* @tower_hanoi, { 2, 1, 0 }
  uselistorder i32 0, { 0, 4, 7, 8, 6, 1, 3, 9, 2, 5 }
  uselistorder i32 (i8*, ...)* @printf, { 2, 1, 0, 3 }
  uselistorder i1 false, { 2, 6, 7, 3, 4, 5, 0, 8, 1 }
  uselistorder i64 0, { 7, 8, 9, 10, 11, 12, 2, 3, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0, 26, 4, 1, 27, 5, 6, 25 }
}

define i64 @_fini() local_unnamed_addr {
dec_label_pc_1848:
  %0 = alloca i64
  %1 = load i64, i64* %0
  ret i64 %1, !insn.addr !172

; uselistorder directives
  uselistorder i32 1, { 1, 13, 20, 19, 2, 14, 22, 15, 10, 9, 8, 7, 6, 5, 4, 3, 16, 17, 18, 11, 0, 21, 12 }
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

!0 = !{i64 4096}
!1 = !{i64 4104}
!2 = !{i64 4111}
!3 = !{i64 4114}
!4 = !{i64 4116}
!5 = !{i64 4122}
!6 = !{i64 4276}
!7 = !{i64 4292}
!8 = !{i64 4308}
!9 = !{i64 4324}
!10 = !{i64 4340}
!11 = !{i64 4356}
!12 = !{i64 4372}
!13 = !{i64 4388}
!14 = !{i64 4404}
!15 = !{i64 4447}
!16 = !{i64 4453}
!17 = !{i64 4504}
!18 = !{i64 4568}
!19 = !{i64 4580}
!20 = !{i64 4587}
!21 = !{i64 4590}
!22 = !{i64 4601}
!23 = !{i64 4603}
!24 = !{i64 4610}
!25 = !{i64 4615}
!26 = !{i64 4620}
!27 = !{i64 4628}
!28 = !{i64 4632}
!29 = !{i64 4644}
!30 = !{i64 4649}
!31 = !{i64 4709}
!32 = !{i64 4686}
!33 = !{i64 4678}
!34 = !{i64 4690}
!35 = !{i64 4693}
!36 = !{i64 4714}
!37 = !{i64 4747}
!38 = !{i64 4751}
!39 = !{i64 4753}
!40 = !{i64 4759}
!41 = !{i64 4776}
!42 = !{i64 4794}
!43 = !{i64 4806}
!44 = !{i64 4808}
!45 = !{i64 4816}
!46 = !{i64 4850}
!47 = !{i64 4859}
!48 = !{i64 4862}
!49 = !{i64 4868}
!50 = !{i64 4885}
!51 = !{i64 4903}
!52 = !{i64 4911}
!53 = !{i64 4913}
!54 = !{i64 4917}
!55 = !{i64 4921}
!56 = !{i64 4925}
!57 = !{i64 4931}
!58 = !{i64 4970}
!59 = !{i64 4975}
!60 = !{i64 4980}
!61 = !{i64 5024}
!62 = !{i64 5031}
!63 = !{i64 5032}
!64 = !{i64 5055}
!65 = !{i64 5061}
!66 = !{i64 5064}
!67 = !{i64 5070}
!68 = !{i64 5092}
!69 = !{i64 5097}
!70 = !{i64 5103}
!71 = !{i64 5106}
!72 = !{i64 5112}
!73 = !{i64 5137}
!74 = !{i64 5142}
!75 = !{i64 5148}
!76 = !{i64 5151}
!77 = !{i64 5157}
!78 = !{i64 5182}
!79 = !{i64 5187}
!80 = !{i64 5193}
!81 = !{i64 5196}
!82 = !{i64 5221}
!83 = !{i64 5573}
!84 = !{i64 5577}
!85 = !{i64 5287}
!86 = !{i64 5277}
!87 = !{i64 5279}
!88 = !{i64 5291}
!89 = !{i64 5294}
!90 = !{i64 5296}
!91 = !{i64 5298}
!92 = !{i64 5310}
!93 = !{i64 5312}
!94 = !{i64 5318}
!95 = !{i64 5321}
!96 = !{i64 5327}
!97 = !{i64 5333}
!98 = !{i64 5339}
!99 = !{i64 5357}
!100 = !{i64 5362}
!101 = !{i64 5366}
!102 = !{i64 5393}
!103 = !{i64 5396}
!104 = !{i64 5408}
!105 = !{i64 5410}
!106 = !{i64 5416}
!107 = !{i64 5419}
!108 = !{i64 5425}
!109 = !{i64 5434}
!110 = !{i64 5440}
!111 = !{i64 5458}
!112 = !{i64 5463}
!113 = !{i64 5467}
!114 = !{i64 5491}
!115 = !{i64 5494}
!116 = !{i64 5506}
!117 = !{i64 5508}
!118 = !{i64 5514}
!119 = !{i64 5517}
!120 = !{i64 5523}
!121 = !{i64 5532}
!122 = !{i64 5538}
!123 = !{i64 5556}
!124 = !{i64 5561}
!125 = !{i64 5565}
!126 = !{i64 5583}
!127 = !{i64 5589}
!128 = !{i64 5592}
!129 = !{i64 5604}
!130 = !{i64 5607}
!131 = !{i64 5609}
!132 = !{i64 5619}
!133 = !{i64 5625}
!134 = !{i64 5630}
!135 = !{i64 5636}
!136 = !{i64 5646}
!137 = !{i64 5648}
!138 = !{i64 5654}
!139 = !{i64 5659}
!140 = !{i64 5667}
!141 = !{i64 5711}
!142 = !{i64 5718}
!143 = !{i64 5719}
!144 = !{i64 5740}
!145 = !{i64 5781}
!146 = !{i64 5790}
!147 = !{i64 5795}
!148 = !{i64 5807}
!149 = !{i64 5817}
!150 = !{i64 5736}
!151 = !{i64 5837}
!152 = !{i64 5864}
!153 = !{i64 5874}
!154 = !{i64 5925}
!155 = !{i64 5942}
!156 = !{i64 5965}
!157 = !{i64 5975}
!158 = !{i64 6004}
!159 = !{i64 6010}
!160 = !{i64 6074}
!161 = !{i64 6086}
!162 = !{i64 6091}
!163 = !{i64 6105}
!164 = !{i64 6129}
!165 = !{i64 6154}
!166 = !{i64 6166}
!167 = !{i64 6171}
!168 = !{i64 6183}
!169 = !{i64 6192}
!170 = !{i64 6194}
!171 = !{i64 6213}
!172 = !{i64 6228}
