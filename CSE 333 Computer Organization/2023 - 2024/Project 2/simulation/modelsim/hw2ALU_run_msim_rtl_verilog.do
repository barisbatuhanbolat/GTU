transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/ALUand.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/ALUor.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/ALUxor.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/ALUnor.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/alu.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/fullAdder.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/adder.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/cla_4bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/cla_16bit.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/subtractor.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/mod_dp.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/mod_cu.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/mod.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/comparator.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/ALUless_than.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/_8x1Mux.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/_4x1Mux.v}
vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/_2x1Mux.v}

vlog -vlog01compat -work work +incdir+C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2 {C:/Users/Baris/Desktop/quartusProjects/CSE331/hw2/alu_testbench.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cyclonev_ver -L cyclonev_hssi_ver -L cyclonev_pcie_hip_ver -L rtl_work -L work -voptargs="+acc"  alu_testbench

add wave *
view structure
view signals
run -all
