#ifndef PIPELINE_RENDERINGENGINE_H_GUARD
#define PIPELINE_RENDERINGENGINE_H_GUARD


#include "Common.h"


#include "RHIBuffer.h"
#include "RHISwapchain.h"
#include "RHIDevice.h"
#include "RHIGraphicPipeline.h"


#include "objModel.h"

namespace pipeline {




    // ����vulkanӦ������Ҫ��windows
    // ����vulkan instanceʵ��������ָ������Ҫ��vulkanʵ����չ
    // ����window��instance����ȡ����Ҫ��surface����
    // ѡ�������豸����
    // �����߼��豸���󣬿���ָ���߼��豸����Ҫ����չ�ӿڣ�����swapchain
    // �����߼��豸��Ӧ��swapchain��swapchainimage
    // ������Ⱦframebuffer��framebuffer��Ҫͨ��image viewȥ����swap chain image


    // command pool ���� command buffer
    // command buffer ��render pass�� frame buffer�� graphic pipeline
    // render pass ָ�� color attachment�Ĳ�����ʽ
    // frame bufferָ��swap chain�е�image view -��swap chain��Ӧ��image
    // graphic pipelineָ��fixed pipeline�е�״̬��shader module
    //

    // VkPipelineLayout��VkPipeline�Ĺ��ܲ���
    // VkPipelineLayout����VkDescriptorSetLayout��push const 
    // VkDescriptorSetLayout������ͨ��VkDescriptorSetLayoutBinding����VkPipelineLayout��Descriptor�Ĳ��֣�
    // һ��VkPipeline��Ӧһ��VkPipelineLayout��һ��VkPipelineLayout��Ӧһ�����߶��VkDescriptorSetLayout��
    // 
    // VkDescriptorSet���Ǿ�����ƹ��̣�һ��drawcall����Ӧ��uniform buffer��textrue sampe����Ϣ��ͨ��VkDescriptorSetLayout���ֽ��д�����
    // ÿ��drawcall����VkPipeline�Ͷ�Ӧ��VkPipelineLayout���Լ�����VkDescriptorSet
    // ����10����ͬ��ģ�Ͳ���ͬ���pipeline���ƣ���������ͬ��VkPipeline��VkPipelineLayout��
    // �Ѿ�ÿ��ģ�͸��Ե�VkDescriptorSet�����а����˸��Ե�sample��uniform buffer��shader storage buffer�����в���


    // ��Ⱦ�������첽�ģ���ȡswap chain image��ִ��command buffer�����ѽ��д��swap chain image��д����ɺ���Խ���present
    // ������ڼ������⣺
    // 1����ȡswap chain image���ܻ���ʹ�ã���Ҫ�ȴ���ʹ���ꣻ
    // 2��ִ��command buffer��ִ������Ҫ��֪���������̣������д�룻
    // 3��presnet���̵�ʱ����Ҫ�ȴ�����֪swap chain image�Ѿ�д����ɣ����Խ��г��֣�

    // ���Էֳ��������̣���Ⱦ���̺ͳ������̣�
    // ��Ⱦ������Ҫ����VkSemaphore��
    // 1���ȴ�swap chain image��ȡ�ɹ�������д���imageAvailableSemaphore
    // 2��ִ��command buffer����Ⱦ���д��swap chain image��ɣ���֪�������̵�renderFinishedSemaphore
    // ����������Ҫһ��VkSemaphore��
    // 1��swap chain image��Ⱦ���д����ɣ��ɱ�����renderFinishedSemaphore

    // �������̣�
    // ��ȡ���õ�swap chain image index��
    // reset command buffer
    // ��ʼ��¼command buffer��ָ��render pass��pipeline��image indexָ����framebuffer��
    // ����VkSubmitInfo��ָ��imageAvailableSemaphore��renderFinishedSemaphore���ύִ��vkQueueSubmit
    // 
    // �������̣�
    // ����VkPresentInfoKHR��ָ��renderFinishedSemaphore��vkQueuePresentKHR

    
    class IPreRender;
    class IRenderTarget;
    
    class kSGNode;
    class kScene;
    class kCamera;


    class kRenderQueueManager;
    class kRenderTargetManager;
    class kPreRenderManager;
    class kGPUResourceManager;
    class kRenderPipelineManager;
    
    class kWinInfo
    {
    public:
        kWinInfo() {
            pwindow = nullptr;
            width = 0;
            height = 0;
        }

        GLFWwindow* pwindow;
        uint32_t    width;
        uint32_t    height;
    };
    
    
    class kRenderingEngine
    {
    public:
        kRenderingEngine();
        virtual ~kRenderingEngine();

        //------------------------------------------------------------------------------
        //	Desc:	The function Configure configures the rendering engine 
        //			according to the config file, whose file name is the input 
        //			parameter ConfigFileName. When the string ConfigFileName is 
        //			empty or the file can not be found, the function uses the default 
        //			settings. This function should be called just after CRenderingEngine 
        //			object is constructed. OnConfigure as an over-writable function is 
        //			invoked in Configure, which gives developers opportunity to 
        //			configure rendering engine in desired way. If OnConfigure returns 
        //			non-zero value, the default configuration is skipped.
        //
        //------------------------------------------------------------------------------
        virtual int Configure(const std::string& ConfigFileName);

        //------------------------------------------------------------------------------
        //	Desc:	The function Initialize initializes the rendering engine when the 
        //			rendering output window is ready. It should not be invoked before 
        //			invoking the function Configure. The input parameter is a WinInfo 
        //			object, which specifies the parameters of the rendering output 
        //			window. 
        //
        //------------------------------------------------------------------------------
        virtual int Initialize(const kWinInfo& wininfo);

        //------------------------------------------------------------------------------
        //	Desc:	The function stops the render engine, and release the window 
        //			related resources allocated for the engine. When the engine is 
        //			finalized, the states inside the engine are set back to the 
        //			uninitialized but configured states. That is, after calling the 
        //			function Finalize, the function Initialize should be called again, 
        //			but no need to call the function Configure if the engine is to be 
        //			reused again. The destructor calls this function automatically. 
        //------------------------------------------------------------------------------
        virtual void Finalize();

        //------------------------------------------------------------------------------
        //	Desc:	The function OpenSceneModel is to open a scene model whose name
        //			is given by the input parameter SceneModelName, and set the 
        //			to-be-rendered scene graph. The string SceneModelName can be the 
        //			full path of the file, or just file name. When the string 
        //			SceneModelName is empty or the scene model can not be found in 
        //			default path, the function will return 0. It should be called 
        //			after calling Configure and Initialize. After executing 
        //			OpenSceneModel, the first kd-tree is regarded as the default 
        //			render traverse root. Moreover, according to the first kd-tree 
        //			(or the scene graph corresponding to the kd-tree), the engine's 
        //			internal camera is set to a set of default values. It means after 
        //			calling OpenSceneModel, developers can use GetCamera to retrieve 
        //			the default viewing parameters.
        //
        //	param:	SceneModelName is the full path of vdb, such as:J:\\a\\a.vdb
        //			
        //			return true if successful, else return false.			
        //------------------------------------------------------------------------------
        int OpenSceneModel(const std::string& SceneModelName, int ActiveSceneGraph = 0);
        void CloseSceneModel();


        //------------------------------------------------------------------------------
        //	Desc:	The function does all rendering tasks to generate one image in 
        //			the back frame buffer of the rendering output window, with respect 
        //			to the internal camera. By default, it renders the entities in the 
        //			active scene graph. For most walk-through application, the 
        //			application developers should call SetCamera and DoRendering at 
        //			certain rate with the changing viewing parameters. 
        //
        //------------------------------------------------------------------------------
        void ClearScreen(float r = 0.0f, float g = 0.3f, float b = 0.9f, float a = 0.0f);
        void DoRendering();
        void SwapBuffers();

        void FrameChanged() { m_FramebufferResized = true; }

    protected:

        void CreateSyncObjects();
        void CreateCommandBuffers();
        void BuildCommandBuffer(uint32_t imageIndex);

        void RecreateSwapChain();

        void SetRenderTraverseRoot( const std::vector<kSGNode*>& roots );
        void SetCamera(kCamera& Camera );
        void GetCamera(kCamera& Camera );
        
        
    protected:

        kRenderQueueManager*					GetRenderQueueManager()		{return m_pRenderQueueMgr;}
        kRenderTargetManager*					GetRenderTargetManager()	{return m_pRenderTargetMgr;}
        kPreRenderManager*						GetPreRenderManager()		{return m_pPreRenderMgr;}
        kGPUResourceManager*				    GetGPUResourceManager()	    {return m_pGPUResourceMpr;}
        kRenderPipelineManager*					GetRenderPipelineManager()	{return m_pRenderPipelineMgr;}
        
    protected:
        
        virtual int RegisterPreRenderPrototypes();
        virtual int RegisterRenderPipelinePrototypes();
        
        // user override functions
        virtual int OnConfigure();
        virtual int OnRegisterPreRenderPrototypes();
        virtual int OnRegisterRenderPipelinePrototypes();
        
    protected:
        
        kWinInfo								m_WinInfo;


        kRHIDevice						        m_Context;
        kRHISwapchain					        m_Swapchain;
        bool							        m_FramebufferResized = false;


        // Acquire an image from the swap chain
        // Execute commands that draw onto the acquired image
        // Present that image to the screen for presentation, returning it to the swapchain
        //
        // Semaphore
        // 
        // A semaphore is either unsignaled or signaled. It begins life as unsignaled. The way 
        // we use a semaphore to order queue operations is by providing the same semaphore as 
        // a 'signal' semaphore in one queue operation and as a 'wait' semaphore in another 
        // queue operation. For example, lets say we have semaphore S and queue operations A 
        // and B that we want to execute in order. What we tell Vulkan is that operation A will 
        // 'signal' semaphore S when it finishes executing, and operation B will 'wait' on 
        // semaphore S before it begins executing. When operation A finishes, semaphore S 
        // will be signaled, while operation B wont start until S is signaled. After operation 
        // B begins executing, semaphore S is automatically reset back to being unsignaled, 
        // allowing it to be used again.
        // Note that in this code snippet, both calls to vkQueueSubmit() return immediately - 
        // the waiting only happens on the GPU. The CPU continues running without blocking. 
        // To make the CPU wait, we need a different synchronization primitive, Fence.
        //
        // Fence
        //
        // A fence has a similar purpose, in that it is used to synchronize execution, but 
        // it is for ordering the execution on the CPU, otherwise known as the host. Simply 
        // put, if the host needs to know when the GPU has finished something, we use a fence.
        // A concrete example is taking a screenshot. Say we have already done the necessary 
        // work on the GPU. Now need to transfer the image from the GPU over to the host and 
        // then save the memory to a file. We have command buffer A which executes the transfer 
        // and fence F. We submit command buffer A with fence F, then immediately tell the host 
        // to wait for F to signal. This causes the host to block until command buffer A finishes 
        // execution. Thus we are safe to let the host save the file to disk, as the memory 
        // transfer has completed.
        // Unlike the semaphore example, this example does block host execution. This means the 
        // host won't do anything except wait until execution has finished. For this case, we 
        // had to make sure the transfer was complete before we could save the screenshot to disk.

        std::vector<VkSemaphore>		        m_ImageAvailableSemaphores;
        std::vector<VkSemaphore>		        m_RenderFinishedSemaphores;
        std::vector<VkFence>			        m_InFlightFences;
        std::vector<VkCommandBuffer>	        m_CommandBuffers;
        uint32_t						        m_CurrentFrame = 0;

        
        kGPUResourceManager*				    m_pGPUResourceMpr;
        kRenderQueueManager*   					m_pRenderQueueMgr;
        kRenderTargetManager*					m_pRenderTargetMgr;
        kPreRenderManager*						m_pPreRenderMgr;
        kRenderPipelineManager*					m_pRenderPipelineMgr;

        std::vector<kSGNode*>	                m_TraverseRoots;

        IPreRender*								m_pStartPreRender;
        IRenderTarget*						    m_pPrimeTarget;

    protected:

        kRHIGraphicPipeline				        m_GraphicPipeline;
        Model							        m_Model;
    };

}

#endif
