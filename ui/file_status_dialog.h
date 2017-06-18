//
// PROJECT:         Aspia Remote Desktop
// FILE:            ui/file_status_dialog.h
// LICENSE:         See top-level directory
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_UI__FILE_STATUS_DIALOG_H
#define _ASPIA_UI__FILE_STATUS_DIALOG_H

#include "ui/base/dialog.h"
#include "ui/base/edit.h"
#include "base/message_loop/message_loop_thread.h"

namespace aspia {

class UiFileStatusDialog :
    private UiDialog,
    private MessageLoopThread::Delegate
{
public:
    class Delegate
    {
    public:
        virtual void OnWindowClose() = 0;
    };

    UiFileStatusDialog(Delegate* delegate);
    ~UiFileStatusDialog();

    void OnDirectoryOpen(const std::wstring& path);
    void OnFileSend(const std::wstring& path);
    void OnFileRecieve(const std::wstring& path);

private:
    // Dialog implementation.
    INT_PTR OnMessage(UINT msg, WPARAM wparam, LPARAM lparam) override;

    // MessageLoopThread::Delegate implementation.
    void OnBeforeThreadRunning() override;
    void OnAfterThreadRunning() override;

    void OnInitDialog();
    void OnSize(int width, int height);

    Delegate* delegate_ = nullptr;

    MessageLoopThread ui_thread_;
    std::shared_ptr<MessageLoopProxy> runner_;

    DISALLOW_COPY_AND_ASSIGN(UiFileStatusDialog);
};

} // namespace aspia

#endif // _ASPIA_UI__FILE_STATUS_DIALOG_H