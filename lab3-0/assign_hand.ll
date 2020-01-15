; ModuleID = 'assign_hand.ll'
;头部是一些文件名，以及相关硬件的参数,这些参数设置部分都是借鉴于assign.ll文件。
;但需要注意的是:attributes中的'noinline nounwind optnone uwtable'不能使用，否则无法更改注释等，
;每次执行完后会自动恢复
source_filename = "assign.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

;这里定义了main函数，定义了变量a，并附初始值1，之后返回值从a的地址拿到值，将1返回。
;align是4个字节的对齐方式.
;dso_local是一个Runtime Preemption,表明该变量会在同一个链接单元内解析符号.

define dso_local i32 @main() #0 {
  %a = alloca i32, align 4
  store i32 1, i32* %a, align 4
  %return = load i32, i32* %a, align 4
  ret i32 %return
}
;这里是一些属性的设置
attributes #0 = {"correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
