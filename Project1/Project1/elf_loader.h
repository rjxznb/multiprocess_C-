#pragma once

struct bin_loader {
	void(*bin_parm)();
	void(*dy_parm)();
	void(*coredump_parm)();
};
