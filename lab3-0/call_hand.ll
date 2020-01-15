; ModuleID = 'call.c'
;可以将两个函数设置为相同的'#0',之后的‘attribute #0’就会对两个均适用
source_filename = "call.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

;函数callee，通过参数%a获取传入值并返回
define dso_local i32 @callee(i32 %a) #0 {
  %doublea = mul nsw i32 2, %a
  ret i32 %doublea
}
;直接将立即数10作为参数传入，将调用callee的返回值作为main函数的返回值
define dso_local i32 @main() #0 {
  %return = call i32 @callee(i32 10)
  ret i32 %return 
}

attributes #0 = {"correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
