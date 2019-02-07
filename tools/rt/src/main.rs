extern crate getopts;

mod librt;

use getopts::Options;
use std::env;

static PREFIX: &str = "[Rt]";

fn main() {
    let args: librt::InputArgs;
    
    args = match handle_opts() {
        Ok(x) => {
            x
        }
        Err(why) => {
            println!("{} Error: {}", PREFIX,  why.to_string());
            return;
        }
    };

    println!("Args: {:?}", args);
}

fn handle_opts() -> Result<librt::InputArgs, String> {
    let cmdline: Vec<String> = env::args().collect();
    let mut opts = Options::new();
    let mut arch: String;
    let mut mem: String;
    let mut layer: String;
    let mut args: librt::InputArgs;


    args = librt::InputArgs {
        help: false,
        clean: false,
        arch: String::from(""),
        mem: String::from(""),
        layer: String::from(""),
    };

    opts.optopt("a", "arch", "Compile the specified architecture", "ARCH");
    opts.optopt("m", "memory", "The amount of memory for the Qemu", "SIZE");
    opts.optopt("b", "build", "The layer to build", "LAYER");

    opts.optflag("h", "help", "Print this menu");
    opts.optflag("c", "clean", "lean the build directory");

    let found = match opts.parse(&cmdline[1..]) {
        Ok(f) => { 
            f 
        }
        // Return a wrapped err ?
        Err(why) => { 
            return Err(why.to_string());
        }
    };

    if found.opt_present("h") {
        args.help = true;    
    }
    else {
        args.help = false;
    }

    if found.opt_present("c") {
        args.clean = true;
    }
    else {
        args.clean = false;
    }

    args.arch = match found.opt_str("a") {
        Some(x) => {
            verify_arch(x.as_str())?;
            x
        }

        None => { 
            "".to_string()
        }
    };

    args.mem = match found.opt_str("m") {
        Some(x) => {
            verify_mem(x.as_str())?;
            x
        }

        None => { 
            "".to_string()
        }
    };

    args.layer = match found.opt_str("b") {
        Some(x) => {
            verify_layer(x.as_str())?;
            x
        }

        None => { 
            "".to_string()
        }
    };

    Ok(args)
}

fn verify_arch(arch: &str) -> Result<(), String> {
    for x in 0..(librt::ARCH.len()) {
        if librt::ARCH[x] == arch {
            return Ok(());
        }
    }

    Err("Architecture not supported".to_string())
}

fn verify_mem(size: &str) -> Result<(), String> {
    let idx: usize = size.len() - 1;
    let size_suffix: Vec<char> = vec!['b', 'k', 'm', 'g'];
    let size_vec: Vec<char> = size.chars().collect();
    let last_char: char;
    
    last_char = match size_vec[idx].to_lowercase().nth(0) {
        Some(x) => {
            x
        }
        None => {
            return Err("Unable to verify memory size".to_string());
        }
    };

    if size_suffix.contains(&last_char) {
        return Ok(());
    }

    Err("Invalid memory suffix".to_string())
}

fn verify_layer(layer: &str) -> Result<(), String> {
    for x in 0..(librt::LAYER.len()) {
        if librt::LAYER[x] == layer {
            return Ok(());
        }
    }

    Err("Unknown layer".to_string())
}
