mod parsers;

fn main() {
    //let r = parsers::parse_u64("184467440737095518 ").expect("D:      Sadge");
    //let r = parsers::parse_u64("1 ").expect("");
    //let r = parsers::parse_i64("-92233720368547758079223372036854775807 ").expect("");
    println!("{}", r.value)
}

// 10 * accum = accum << 3 + 2*accum
// accum << 3 + 2*accum + b > MAX
//

// check if accum * 8 will overflow
//
