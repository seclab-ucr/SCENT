; ModuleID = 'get_sign_new3.bc'
source_filename = "get_sign.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [7 x i8] c"hello\0A\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@x = common global i32 0, align 4, !dbg !0
@.str.2 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@y = common global i32 0, align 4, !dbg !6

; Function Attrs: noinline nounwind optnone uwtable
define i32 @get_sign(i32 %x, i32 %y) #0 !dbg !13 {
entry:
  %retval = alloca i32, align 4
  %x.addr = alloca i32, align 4
  %y.addr = alloca i32, align 4
  store i32 %x, i32* %x.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %x.addr, metadata !16, metadata !DIExpression()), !dbg !17
  store i32 %y, i32* %y.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %y.addr, metadata !18, metadata !DIExpression()), !dbg !19
  %0 = load i32, i32* %x.addr, align 4, !dbg !20
  %cmp = icmp eq i32 %0, -10, !dbg !22
  br i1 %cmp, label %if.then, label %if.end, !dbg !23

if.then:                                          ; preds = %entry
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0)), !dbg !24
  store i32 0, i32* %retval, align 4, !dbg !26
  br label %return, !dbg !26

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %y.addr, align 4, !dbg !27
  %cmp1 = icmp slt i32 %1, 0, !dbg !29
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !30

if.then2:                                         ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !31
  br label %return, !dbg !31

if.else:                                          ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !32
  br label %return, !dbg !32

return:                                           ; preds = %if.else, %if.then2, %if.then
  %2 = load i32, i32* %retval, align 4, !dbg !33
  ret i32 %2, !dbg !33
}

; Function Attrs: nounwind readnone speculatable
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define void @Model0_Symbolize() #0 !dbg !34 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %a, metadata !37, metadata !DIExpression()), !dbg !38
  %0 = bitcast i32* %a to i8*, !dbg !39
  call void @klee_make_symbolic(i8* %0, i64 4, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i32 0, i32 0)), !dbg !40
  %1 = load i32, i32* %a, align 4, !dbg !41
  store i32 %1, i32* @x, align 4, !dbg !42
  call void @llvm.dbg.declare(metadata i32* %b, metadata !43, metadata !DIExpression()), !dbg !44
  %2 = bitcast i32* %b to i8*, !dbg !45
  call void @klee_make_symbolic(i8* %2, i64 4, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !46
  %3 = load i32, i32* %b, align 4, !dbg !47
  store i32 %3, i32* @y, align 4, !dbg !48
  ret void, !dbg !49
}

declare void @klee_make_symbolic(i8*, i64, i8*) #2

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 !dbg !50 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @Model0_Symbolize(), !dbg !53
  store i32 -10, i32* @x, align 4, !dbg !54
  %0 = load i32, i32* @x, align 4, !dbg !55
  %1 = load i32, i32* @y, align 4, !dbg !56
  %call = call i32 @get_sign(i32 %0, i32 %1), !dbg !57
  ret i32 %call, !dbg !58
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!9, !10, !11}
!llvm.ident = !{!12}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 24, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 6.0.0 (tags/RELEASE_600/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5)
!3 = !DIFile(filename: "get_sign.c", directory: "/home/yue/Work/KLEE_Platform/klee/examples/get_sign")
!4 = !{}
!5 = !{!0, !6}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 24, type: !8, isLocal: false, isDefinition: true)
!8 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!9 = !{i32 2, !"Dwarf Version", i32 4}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{!"clang version 6.0.0 (tags/RELEASE_600/final)"}
!13 = distinct !DISubprogram(name: "get_sign", scope: !3, file: !3, line: 6, type: !14, isLocal: false, isDefinition: true, scopeLine: 6, flags: DIFlagPrototyped, isOptimized: false, unit: !2, variables: !4)
!14 = !DISubroutineType(types: !15)
!15 = !{!8, !8, !8}
!16 = !DILocalVariable(name: "x", arg: 1, scope: !13, file: !3, line: 6, type: !8)
!17 = !DILocation(line: 6, column: 18, scope: !13)
!18 = !DILocalVariable(name: "y", arg: 2, scope: !13, file: !3, line: 6, type: !8)
!19 = !DILocation(line: 6, column: 25, scope: !13)
!20 = !DILocation(line: 7, column: 7, scope: !21)
!21 = distinct !DILexicalBlock(scope: !13, file: !3, line: 7, column: 7)
!22 = !DILocation(line: 7, column: 9, scope: !21)
!23 = !DILocation(line: 7, column: 7, scope: !13)
!24 = !DILocation(line: 8, column: 7, scope: !25)
!25 = distinct !DILexicalBlock(scope: !21, file: !3, line: 7, column: 16)
!26 = !DILocation(line: 9, column: 6, scope: !25)
!27 = !DILocation(line: 12, column: 7, scope: !28)
!28 = distinct !DILexicalBlock(scope: !13, file: !3, line: 12, column: 7)
!29 = !DILocation(line: 12, column: 9, scope: !28)
!30 = !DILocation(line: 12, column: 7, scope: !13)
!31 = !DILocation(line: 13, column: 6, scope: !28)
!32 = !DILocation(line: 15, column: 6, scope: !28)
!33 = !DILocation(line: 16, column: 1, scope: !13)
!34 = distinct !DISubprogram(name: "Model0_Symbolize", scope: !3, file: !3, line: 25, type: !35, isLocal: false, isDefinition: true, scopeLine: 25, isOptimized: false, unit: !2, variables: !4)
!35 = !DISubroutineType(types: !36)
!36 = !{null}
!37 = !DILocalVariable(name: "a", scope: !34, file: !3, line: 26, type: !8)
!38 = !DILocation(line: 26, column: 9, scope: !34)
!39 = !DILocation(line: 27, column: 24, scope: !34)
!40 = !DILocation(line: 27, column: 5, scope: !34)
!41 = !DILocation(line: 28, column: 9, scope: !34)
!42 = !DILocation(line: 28, column: 7, scope: !34)
!43 = !DILocalVariable(name: "b", scope: !34, file: !3, line: 29, type: !8)
!44 = !DILocation(line: 29, column: 9, scope: !34)
!45 = !DILocation(line: 30, column: 24, scope: !34)
!46 = !DILocation(line: 30, column: 5, scope: !34)
!47 = !DILocation(line: 31, column: 9, scope: !34)
!48 = !DILocation(line: 31, column: 7, scope: !34)
!49 = !DILocation(line: 32, column: 1, scope: !34)
!50 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 33, type: !51, isLocal: false, isDefinition: true, scopeLine: 33, isOptimized: false, unit: !2, variables: !4)
!51 = !DISubroutineType(types: !52)
!52 = !{!8}
!53 = !DILocation(line: 42, column: 3, scope: !50)
!54 = !DILocation(line: 43, column: 5, scope: !50)
!55 = !DILocation(line: 48, column: 19, scope: !50)
!56 = !DILocation(line: 48, column: 22, scope: !50)
!57 = !DILocation(line: 48, column: 10, scope: !50)
!58 = !DILocation(line: 48, column: 3, scope: !50)
