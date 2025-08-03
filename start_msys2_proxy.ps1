# MSYS2代理启动脚本 (PowerShell)
# 使用方法：.\start_msys2_proxy.ps1

Write-Host "开始设置MSYS2代理..." -ForegroundColor Green

# 检查MSYS2是否存在
$msys2Path = "D:\msys64\msys2_shell.cmd"
if (-not (Test-Path $msys2Path)) {
    Write-Host "错误：找不到MSYS2安装路径: $msys2Path" -ForegroundColor Red
    exit 1
}

Write-Host "MSYS2路径检查通过: $msys2Path" -ForegroundColor Green

# 设置代理环境变量
$env:http_proxy = "http://127.0.0.1:7890"
$env:https_proxy = "http://127.0.0.1:7890"
$env:HTTP_PROXY = "http://127.0.0.1:7890"
$env:HTTPS_PROXY = "http://127.0.0.1:7890"

Write-Host "代理设置完成：" -ForegroundColor Green
Write-Host "HTTP代理: $env:http_proxy"
Write-Host "HTTPS代理: $env:https_proxy"

# 启动MSYS2
Write-Host "正在启动MSYS2..." -ForegroundColor Yellow
try {
    # 使用Start-Process启动MSYS2
    Start-Process -FilePath $msys2Path -Wait -NoNewWindow
    Write-Host "MSYS2已启动" -ForegroundColor Green
} catch {
    Write-Host "启动MSYS2时出错: $($_.Exception.Message)" -ForegroundColor Red
    
    # 尝试直接调用
    Write-Host "尝试直接调用MSYS2..." -ForegroundColor Yellow
    & $msys2Path
}

Write-Host "脚本执行完成" -ForegroundColor Green 