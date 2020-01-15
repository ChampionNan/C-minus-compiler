; ModuleID = 'while.c'
;参数等设置参考assign_hand.ll的解析
source_filename = "while.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

;%a, %i分别代表对应函数中的变量，并且赋予了初始值，之后直接跳转到while判断模块
define dso_local i32 @main() #0 {
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 10, i32* %a, align 4
  store i32 0, i32* %i, align 4
  br label %while
;这里将i的值从地址中取出与立即数10比较，根据结果判断是在while内还是跳转到while外
  while:
  %cmpi = load i32, i32* %i, align 4
  %cond = icmp slt i32 %cmpi, 10
  br i1 %cond, label %Yes, label %Quit
;while内，更新%I值，并且存入i的地址，之后更新a的值
  Yes:
  %addi1 = load i32, i32* %i, align 4
  %resi = add nsw i32 %addi1, 1
  store i32 %resi, i32* %i, align 4
  %adda = load i32, i32* %a, align 4
  %resa = add nsw i32 %adda, %resi
  store i32 %resa, i32* %a, align 4
  br label %while
;取出a的值作为返回值
  Quit:
  %return = load i32, i32* %a, align 4
  ret i32 %return
}

attributes #0 = {"correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
