#[derive(Debug)]
pub struct InputArgs {
    pub help: bool,
    pub clean: bool,
    pub arch: String,
    pub mem: String,
    pub layer: String,
}

pub const ARCH: &[&str] = &["arm-none-eabi"];
pub const LAYER: &[&str] = &["helium", "regent"];
