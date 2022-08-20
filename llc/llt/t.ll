define i32 @mt(i32 %a, i32 %b) #0 {
    %l = mul nsw i32 %a, %b
    ret i32 %l
}