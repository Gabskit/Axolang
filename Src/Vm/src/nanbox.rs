/// Representación de los tipos de datos BIV según tamaño de variable en Paxo
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PaxoValue {
    /// 16 bits: valor extendido.
    Xs(u16),
    /// 32 bits: valor standard.
    S(u32),
    /// 64 bits: valor medio.
    M(u64),
    /// 128 bits: valor largo.
    L(u128)}

impl PaxoValue {
    /// Bit
    // Empaquetado
    pub fn pack_bit_xs(bit: bool) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b00 << 8; // Payload Tag 00 para Bit
        let payload: u16 = bit as u16;
        PaxoValue::Xs(exp_mask | tag | payload )}

    pub fn pack_bit_s(bit: bool) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b000 << 17; // Payload Tag 000 para Bit
        let payload: u32 = bit as u32;
        PaxoValue::S(exp_mask | tag | payload )}

    pub fn pack_bit_m(bit: bool) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b000 << 47; // Payload Tag 000 para Bit
        let payload: u64 = bit as u64;
        PaxoValue::M(exp_mask | tag | payload )}

    pub fn pack_bit_l(bit: bool) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b000 << 107;                    // Payload Tag 000 para Bit
        let payload: u128 = bit as u128;
        PaxoValue::L(exp_mask | tag | payload )}

    // Desempaquetado
    pub fn unpack_bit_xs(val: u16) -> bool {
        (val & 1) != 0}

    pub fn unpack_bit_s(val: u32) -> bool {
        (val & 1) != 0}

    pub fn unpack_bit_m(val: u64) -> bool {
        (val & 1) != 0}

    pub fn unpack_bit_l(val: u128) -> bool {
        (val & 1) != 0}

    /// Caracter
    // Empaquetado
    pub fn pack_char_xs(c: char) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b01 << 8;           // Payload Tag 01 para Char
        let payload: u16 = c as u16;
        PaxoValue::Xs(exp_mask | tag | payload)}

    pub fn pack_char_s(c: char) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b010 << 17;              // Payload Tag 010 para Char
        let payload: u32 = c as u32;
        PaxoValue::S(exp_mask | tag | payload)}

    pub fn pack_char_m(c: char) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b010 << 47;                 // Payload Tag 010 para Char
        let payload: u64 = c as u64;
        PaxoValue::M(exp_mask | tag | payload)}

    pub fn pack_char_l(c: char) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b010 << 107;                    // Payload Tag 010 para Char
        let payload: u128 = c as u128;
        PaxoValue::L(exp_mask | tag | payload)}

    // Desempaquetado 
    pub fn unpack_char_xs(val: u16) -> char {
        val as u8 as char}

    pub fn unpack_char_s(val: u32) -> char {
        val as u16 as char}

    pub fn unpack_char_m(val: u64) -> char {
        val as u32 as char}

    pub fn unpack_char_l(val: u128) -> char {
        val as u32 as char}

    /// Vectores 2d 
    // Empaquetado 
    pub fn pack_vec2d_xs(x: i8, y: i8) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b10 << 8;           // Payload Tag 10 para Vec2D
        let x_bits = ((x as u8 & 0x0F) as u16) << 4;
        let y_bits = (y as u8 & 0x0F) as u16;
        PaxoValue::Xs(exp_mask | tag | x_bits | y_bits)}

    pub fn pack_vec2d_s(x: i8, y: i8, is_polar: bool) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b010 << 17;              // Payload Tag 010 para Vec2D
        let polar_bit: u32 = if is_polar { 1 << 16 } else { 0 }; // *i bit
        let x_bits = (x as u8 as u32) << 8;
        let y_bits = y as u8 as u32;

        PaxoValue::S(exp_mask | tag | polar_bit | x_bits | y_bits)}

    pub fn pack_vec2d_m(x: i32, y: i32, is_polar: bool) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b010 << 47;                 // Payload Tag 010 para Vec2D
        let polar_bit: u64 = if is_polar { 1 << 46 } else { 0 }; // *i bit
        let x_bits = ((x as i32 as u64) & 0x7FFFFF) << 23;
        let y_bits = (y as i32 as u64) & 0x7FFFFF;

        PaxoValue::M(exp_mask | tag | polar_bit | x_bits | y_bits)}

    pub fn pack_vec2d_l(x: i64, y: i64, is_polar: bool) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b010 << 107;                    // Payload Tag 010 para Vec2D
        let polar_bit: u128 = if is_polar { 1 << 106 } else { 0 }; // *i bit
        let x_bits = ((x as i64 as u128) & 0x1FFFFFFFFFFFFF) << 53;
        let y_bits = (y as i64 as u128) & 0x1FFFFFFFFFFFFF;

        PaxoValue::L(exp_mask | tag | polar_bit | x_bits | y_bits)}

    // Desempaquetado
    pub fn unpack_vec2d_xs(val: u16) -> (i8, i8) {
        let x = ((val >> 4) & 0x0F) as u8;
        let y = (val & 0x0F) as u8;
        (x as i8, y as i8)}

    pub fn unpack_vec2d_s(val: u32) -> (i8, i8, bool) {
        let is_polar = (val & (1 << 16)) != 0;
        let x = ((val >> 8) & 0xFF) as u8 as i8;
        let y = (val & 0xFF) as u8 as i8;
        (x, y, is_polar)}

    pub fn unpack_vec2d_m(val: u64) -> (i32, i32, bool) {
        let is_polar = (val & (1 << 46)) != 0;
        let x = ((((val >> 23) & 0x7FFFFF) as i64) << 41) >> 41;
        let y = ((((val & 0x7FFFFF) as i64) << 41) >> 41);
        (x as i32, y as i32, is_polar) }

    pub fn unpack_vec2d_l(val: u128) -> (i64, i64, bool) {
        let is_polar = (val & (1 << 106)) != 0;
        let x = ((((val >> 53) & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75;
        let y = ((((val & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75);
        (x as i64, y as i64, is_polar)}}

#[cfg(test)]
mod tests {
    use super::PaxoValue;

    #[test]
    fn vec2d_xs_roundtrip() {
        let packed = PaxoValue::pack_vec2d_xs(10, 5);
        let (x, y) = match packed {
            PaxoValue::Xs(bits) => PaxoValue::unpack_vec2d_xs(bits),
            other => panic!("unexpected variant: {:?}", other),};

        assert_eq!((x, y), (10, 5));}

    #[test]
    fn vec2d_s_roundtrip() {
        let packed = PaxoValue::pack_vec2d_s(10, -5, false);
        let (x, y, polar) = match packed {
            PaxoValue::S(bits) => PaxoValue::unpack_vec2d_s(bits),
            other => panic!("unexpected variant: {:?}", other),};

        assert_eq!((x, y, polar), (10, -5, false));}}