mod parsers;

fn main() {
    let r = parsers::parse_u64("8".to_string());
    match r {
        Ok(x) => println!("{x}"),
        Err(x) => println!("D:")
    }
}
