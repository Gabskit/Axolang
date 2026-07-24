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
        (x as i64, y as i64, is_polar)}

    /// Vector 4d 
    // Empaquetado
    pub fn pack_vec4d_xs(x: i8, y: i8, z: i8, w: i8) -> Self {
        let exp_mask: u16 = 0b11111 << 10; // 5 bits exponente en 1
        let tag: u16 = 0b11 << 8;           // Payload Tag 11 para Vec4D
        let x_bits = ((x as u8 & 0x0F) as u16) << 4;
        let y_bits = (y as u8 & 0x0F) as u16;
        let z_bits = ((z as u8 & 0x0F) as u16) << 4;
        let w_bits = (w as u8 & 0x0F) as u16;
        PaxoValue::Xs(exp_mask | tag | x_bits | y_bits | z_bits | w_bits)}
    
    pub fn pack_vec4d_s(x: i8, y: i8, z: i8, w: i8, is_polar: bool) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b011 << 17;              // Payload Tag 011 para Vec4D
        let polar_bit: u32 = if is_polar { 1 << 16 } else { 0 }; // *i bit
        let x_bits = (x as u8 as u32) << 8;
        let y_bits = (y as u8 as u32) << 8;
        let z_bits = (z as u8 as u32) << 8;
        let w_bits = (w as u8 as u32) << 8;
        PaxoValue::S(exp_mask | tag | polar_bit | x_bits | y_bits | z_bits | w_bits)}

    pub fn pack_vec4d_m(x: i32, y: i32, z: i32, w: i32, is_polar: bool) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b011 << 47;                 // Payload Tag 011 para Vec4D
        let polar_bit: u64 = if is_polar { 1 << 46 } else { 0 }; // *i bit
        let x_bits = ((x as i32 as u64) & 0x7FFFFF) << 23;
        let y_bits = (y as i32 as u64) & 0x7FFFFF;
        let z_bits = ((z as i32 as u64) & 0x7FFFFF) << 23;
        let w_bits = (w as i32 as u64) & 0x7FFFFF;
        PaxoValue::M(exp_mask | tag | polar_bit | x_bits | y_bits | z_bits | w_bits)}
    
    pub fn pack_vec4d_l(x: i64, y: i64, z: i64, w: i64, is_polar: bool) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b011 << 107;                    // Payload Tag 011 para Vec4D
        let polar_bit: u128 = if is_polar { 1 << 106 } else { 0 }; // *i bit
        let x_bits = ((x as i64 as u128) & 0x1FFFFFFFFFFFFF) << 53;
        let y_bits = (y as i64 as u128) & 0x1FFFFFFFFFFFFF;
        let z_bits = ((z as i64 as u128) & 0x1FFFFFFFFFFFFF) << 53;
        let w_bits = (w as i64 as u128) & 0x1FFFFFFFFFFFFF;
        PaxoValue::L(exp_mask | tag | polar_bit | x_bits | y_bits | z_bits | w_bits)}

    // Desempaquetado
    pub fn unpack_vec4d_xs(val: u16) -> (i8, i8, i8, i8) {
        let x = ((val >> 4) & 0x0F) as u8;
        let y = (val & 0x0F) as u8;
        let z = ((val >> 4) & 0x0F) as u8;
        let w = (val & 0x0F) as u8;
        (x as i8, y as i8, z as i8, w as i8)}
    
    pub fn unpack_vec4d_s(val: u32) -> (i8, i8, i8, i8, bool) {
        let is_polar = (val & (1 << 16)) != 0;
        let x = ((val >> 8) & 0xFF) as u8 as i8;
        let y = (val & 0xFF) as u8 as i8;
        let z = ((val >> 8) & 0xFF) as u8 as i8;
        let w = (val & 0xFF) as u8 as i8;
        (x, y, z, w, is_polar)}

    pub fn unpack_vec4d_m(val: u64) -> (i32, i32, i32, i32, bool) {
        let is_polar = (val & (1 << 46)) != 0;
        let x = ((((val >> 23) & 0x7FFFFF) as i64) << 41) >> 41;
        let y = ((((val & 0x7FFFFF) as i64) << 41) >> 41);
        let z = ((((val >> 23) & 0x7FFFFF) as i64) << 41) >> 41;
        let w = ((((val & 0x7FFFFF) as i64) << 41) >> 41);
        (x as i32, y as i32, z as i32, w as i32, is_polar)}
    
    pub fn unpack_vec4d_l(val: u128) -> (i64, i64, i64, i64, bool) {
        let is_polar = (val & (1 << 106)) != 0;
        let x = ((((val >> 53) & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75;
        let y = ((((val & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75);
        let z = ((((val >> 53) & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75;
        let w = ((((val & 0x1FFFFFFFFFFFFF) as i128) << 75) >> 75);
        (x as i64, y as i64, z as i64, w as i64, is_polar)}

    /// Numero complejo
    // Empaquetado
    pub fn pack_complex_s(real: f32, imag: f32) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b100 << 17;              // Payload Tag 011 para Vec4D
        let x_bits = (real.to_bits() as u32) << 8;
        let y_bits = (imag.to_bits() as u32) << 8;
        PaxoValue::S(exp_mask | tag | x_bits | y_bits)}

    pub fn pack_complex_m(real: f32, imag: f32) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b100 << 47;                 // Payload Tag 011 para Vec4D
        let x_bits = (real.to_bits() as u64) << 23;
        let y_bits = (imag.to_bits() as u64) & 0x7FFFFF;
        PaxoValue::M(exp_mask | tag | x_bits | y_bits)}
    
    pub fn pack_complex_l(real: f64, imag: f64) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b100 << 107;                    // Payload Tag 011 para Vec4D
        let x_bits = (real.to_bits() as u128) << 53;
        let y_bits = (imag.to_bits() as u128) & 0x1FFFFFFFFFFFFF;
        PaxoValue::L(exp_mask | tag | x_bits | y_bits)}
    
    // Desempaquetado 
    pub fn unpack_complex_s(val: u32) -> (f32, f32) {
        let x = (val >> 8) as u32;
        let y = (val & 0xFF) as u32;
        (f32::from_bits(x), f32::from_bits(y))}

    pub fn unpack_complex_m(val: u64) -> (f32, f32) {
        let x = (val >> 23) as u32;
        let y = (val & 0x7FFFFF) as u32;
        (f32::from_bits(x), f32::from_bits(y))}

    pub fn unpack_complex_l(val: u128) -> (f64, f64) {
        let x = (val >> 53) as u64;
        let y = (val & 0x1FFFFFFFFFFFFF) as u64;
        (f64::from_bits(x), f64::from_bits(y))}
    
    /// Tiempo
    // Empaquetado
    pub fn pack_time_s(h: u8, m: u8, s: u8) -> Self {
        let exp_mask: u32 = 0b11111111111 << 20; // 11 bits exponente en 1
        let tag: u32 = 0b101 << 17;              // Payload Tag 01 para Vec4D
        let h_bits = (h as u32) << 12;
        let m_bits = (m as u32) << 6;
        let s_bits = s as u32;
        PaxoValue::S(exp_mask | tag | h_bits | m_bits | s_bits)}

    pub fn pack_time_m(d: u8, h: u8, m: u8, s: u8, ms: u16, ns: u16) -> Self {
        let exp_mask: u64 = 0b1111111111111 << 50; // 13 bits exponente en 1
        let tag: u64 = 0b101 << 47;                 // Payload Tag 01 para Vec4D
        let d_bits = (d as u64) << 37;
        let h_bits = (h as u64) << 32;
        let m_bits = (m as u64) << 26;
        let s_bits = (s as u64) << 20;
        let ms_bits = (ms as u64) << 10;
        let ns_bits = ns as u64;
        PaxoValue::M(exp_mask | tag | d_bits | h_bits | m_bits | s_bits | ms_bits | ns_bits)}

    pub fn pack_time_l(d: u8, h: u8, m: u8, s: u8, ms: u16, ns: u16) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b101 << 107;                    // Payload Tag 01 para Vec4D
        let d_bits = (d as u128) << 37;
        let h_bits = (h as u128) << 32;
        let m_bits = (m as u128) << 26;
        let s_bits = (s as u128) << 20;
        let ms_bits = (ms as u128) << 10;
        let ns_bits = ns as u128;
        PaxoValue::L(exp_mask | tag | d_bits | h_bits | m_bits | s_bits | ms_bits | ns_bits)}

    // Desempaquetado 
    pub fn unpack_time_s(val: u32) -> (u8, u8, u8) {
        let h = (val >> 12) as u8;
        let m = (val >> 6) as u8;
        let s = val as u8;
        (h, m, s)}

    pub fn unpack_time_m(val: u64) -> (u8, u8, u8, u8, u16, u16) {
        let d = (val >> 37) as u8;
        let h = (val >> 32) as u8;
        let m = (val >> 26) as u8;
        let s = (val >> 20) as u8;
        let ms = (val >> 10) as u16;
        let ns = val as u16;
        (d, h, m, s, ms, ns)}

    pub fn unpack_time_l(val: u128) -> (u8, u8, u8, u8, u16, u16) {
        let d = (val >> 37) as u8;
        let h = (val >> 32) as u8;
        let m = (val >> 26) as u8;
        let s = (val >> 20) as u8;
        let ms = (val >> 10) as u16;
        let ns = val as u16;
        (d, h, m, s, ms, ns)}

    /// Puntero
    // Empaquetado
    pub fn pack_pointer_l(ptr: u64) -> Self {
        let exp_mask: u128 = 0b11111111111111111 << 110; // 17 bits exponente en 1
        let tag: u128 = 0b110 << 107; // Payload Tag 110 para Puntero
        PaxoValue::L(exp_mask | tag | (ptr as u128))}
    
    // Desempaquetado
    pub fn unpack_pointer_l(val: u128) -> u64 {
        val as u64}}

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