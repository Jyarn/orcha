const SYM_PLUS     : u8 = 43;
const SYM_MINUS    : u8 = 45;
const SYM_SPACE    : u8 = 32;
const SYM_COMMA    : u8 = 44;
const SYM_APOSTROPE: u8 = 39;
const SYM_ZERO     : u8 = 48;
const SYM_NINE     : u8 = 57;
const MAX: u64 = u64::MAX;

#[derive(Debug)]
pub enum Error {
    Overflow,
    SyntaxError
}

pub struct ParseResult<T> {
    pub value: T,
    pub n_read: u64
}

pub fn parse_i64(str: &str) -> Result<ParseResult<i64>, Error> {
    let bytes = str.as_bytes();
    if !(bytes[0] == SYM_PLUS || bytes[0] == SYM_MINUS) {
        return Err(Error::SyntaxError);
    }

    let mut is_negative = 1;
    if bytes[0] == SYM_MINUS {
        is_negative = -1;
    }

    let res = parse_u64(&str[1..])?;
    let m = res.value as i64;

    if m < 0 {
        return Err(Error::Overflow);
    } else {
        return Ok(ParseResult {
            n_read: res.n_read+1,
            value: is_negative * m
        });
    }
}

pub fn parse_u64(str: &str) -> Result<ParseResult<u64>, Error> {
    let mut accum: u64 = 0;
    let mut n_read: u64 = 0;

    for b in str.as_bytes() {
        accum = match *b {
           SYM_COMMA | SYM_APOSTROPE => accum,
           SYM_ZERO..=SYM_NINE => {
                n_read += 1;

                // A u64 will only overflow iff:
                //  1. n_read >= 19
                //  2. 8 * accum overflows ie. accum << 3 overflows
                //  3. 2 * accum + *b > u64::MAX - accum << 3
                //
                //  Note:
                //      10 * accum + b
                //    = 2 * accum + b + 8 * accum
                //    = 2 * accum + b + accum << 3
                //    < uint::MAX
                //
                // overflow <=> 2 * accum + b > uint64::MAX - accum << 3
                //
                if n_read >= 19 && ((accum > ((0xE0 as u64) << 60)) || 2 * accum + (*b as u64) > u64::MAX - (accum << 3)) {
                    return Err(Error::Overflow)
                }

                accum * 10 + (*b as u64 - SYM_ZERO as u64)
           },
           SYM_SPACE => return Ok(ParseResult {
               n_read,
               value: accum
           }),
           _ => return Err(Error::SyntaxError)
        };
    }

    return Err(Error::SyntaxError);
}
