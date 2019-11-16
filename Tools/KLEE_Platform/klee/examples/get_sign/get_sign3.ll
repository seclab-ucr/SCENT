; ModuleID = 'get_sign3.bc'
source_filename = "get_sign.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [2 x i8] c"a\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @get_sign(i16 signext %x) #0 !dbg !7 {
entry:
  %retval = alloca i32, align 4
  %x.addr = alloca i16, align 2
  store i16 %x, i16* %x.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %x.addr, metadata !12, metadata !DIExpression()), !dbg !13
  %0 = load i16, i16* %x.addr, align 2, !dbg !14
  %conv = sext i16 %0 to i32, !dbg !14
  %cmp = icmp eq i32 %conv, 10, !dbg !16
  br i1 %cmp, label %if.then, label %if.end, !dbg !17

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !18
  br label %return, !dbg !18

if.end:                                           ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !19
  br label %return, !dbg !19

return:                                           ; preds = %if.end, %if.then
  %1 = load i32, i32* %retval, align 4, !dbg !20
  ret i32 %1, !dbg !20
}

; Function Attrs: nounwind readnone speculatable
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind optnone uwtable
define i32 @main() #0 !dbg !21 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i16, align 2
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i16* %a, metadata !24, metadata !DIExpression()), !dbg !25
  %0 = bitcast i16* %a to i8*, !dbg !26
  call void @klee_make_symbolic(i8* %0, i64 2, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0)), !dbg !27
  store i16 3, i16* %a, align 2, !dbg !28
  %1 = load i16, i16* %a, align 2, !dbg !29
  %call = call i32 @get_sign(i16 signext %1), !dbg !30
  ret i32 %call, !dbg !31
}

declare void @klee_make_symbolic(i8*, i64, i8*) #2

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 6.0.0 (tags/RELEASE_600/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "get_sign.c", directory: "/home/yue/Work/KLEE_Platform/klee/examples/get_sign")
!2 = !{}
!3 = !{i32 2, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 6.0.0 (tags/RELEASE_600/final)"}
!7 = distinct !DISubprogram(name: "get_sign", scope: !1, file: !1, line: 17, type: !8, isLocal: false, isDefinition: true, scopeLine: 17, flags: DIFlagPrototyped, isOptimized: false, unit: !0, variables: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10, !11}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIBasicType(name: "short", size: 16, encoding: DW_ATE_signed)
!12 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 17, type: !11)
!13 = !DILocation(line: 17, column: 20, scope: !7)
!14 = !DILocation(line: 18, column: 9, scope: !15)
!15 = distinct !DILexicalBlock(scope: !7, file: !1, line: 18, column: 9)
!16 = !DILocation(line: 18, column: 10, scope: !15)
!17 = !DILocation(line: 18, column: 9, scope: !7)
!18 = !DILocation(line: 19, column: 9, scope: !15)
!19 = !DILocation(line: 20, column: 5, scope: !7)
!20 = !DILocation(line: 21, column: 1, scope: !7)
!21 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 23, type: !22, isLocal: false, isDefinition: true, scopeLine: 23, isOptimized: false, unit: !0, variables: !2)
!22 = !DISubroutineType(types: !23)
!23 = !{!10}
!24 = !DILocalVariable(name: "a", scope: !21, file: !1, line: 24, type: !11)
!25 = !DILocation(line: 24, column: 9, scope: !21)
!26 = !DILocation(line: 25, column: 22, scope: !21)
!27 = !DILocation(line: 25, column: 3, scope: !21)
!28 = !DILocation(line: 27, column: 5, scope: !21)
!29 = !DILocation(line: 31, column: 19, scope: !21)
!30 = !DILocation(line: 31, column: 10, scope: !21)
!31 = !DILocation(line: 31, column: 3, scope: !21)
