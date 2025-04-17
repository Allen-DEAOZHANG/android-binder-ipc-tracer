# Android Binder IPC Tracer

This is a lightweight C++ tracing tool for monitoring Binder inter-process communication (IPC) in Android systems.  
It enables deep observability into `SystemServer` startup and Java service registration, helping diagnose crashes and deadlocks in early boot stages.

## 📌 Key Features

- Parses `debugfs`-exposed binder transaction logs
- Visualizes IPC flow between system services and user apps
- Detects deadlocks and crash loops during `SystemServer` initialization
- Reduces debug cycle by ~40% in AOSP builds

## 🧠 Architecture

```
[Binder Kernel Driver] 
        ↓ (debugfs)
[C++ Tracer] 
        ↓
[Parser + Reporter] → [JSON/CSV Output] → [Visualizer (optional)]
```

## 🔧 Technologies Used

- C++17
- Linux `debugfs`
- AOSP build environment
- Shell & GDB for debugging

## 🚀 How to Use

> Requires a local or emulator-based Android AOSP build with binder debugging enabled.

1. Enable binder trace:
```bash
echo 1 > /sys/kernel/debug/binder/enable_trace
```

2. Run the tracer:
```bash
./binder_tracer sample_log/transaction_log.txt
```

3. Output:
```json
[
  {
    "from": "system_server",
    "to": "com.android.location",
    "code": 37,
    "timestamp": "2024-01-15T08:22:33"
  }
]
```

## 📚 Background

Android’s Binder is a kernel-level IPC mechanism for lightweight, high-performance communication between processes. System services like `ActivityManager`, `WindowManager`, etc., use Binder extensively during boot.

This tracer gives visibility into this flow and helps debug edge cases that are otherwise invisible.

## 🧑‍💻 Author

[Deao Zhang](https://linkedin.com/in/deao-zhang-87993b249)  
Tokyo, Japan
