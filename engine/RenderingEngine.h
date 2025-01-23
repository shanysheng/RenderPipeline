#ifndef PIPELINE_RENDERINGENGINE_H_GUARD
#define PIPELINE_RENDERINGENGINE_H_GUARD


#include "Common.h"


#include "BufferGPUResource.h"
#include "RHISwapchain.h"
#include "RHIContext.h"
#include "kGraphicPipeline.h"


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
    class kCameraManager;
    class kRenderTargetManager;
    class kPreRenderManager;
    class kGPUResourceManager;
    class kRenderPipelineManager;
    
    class kWinInfo
    {
    public:
    };
    
    
    class kRenderingEngine
    {
    public:
        kRenderingEngine(void);
        virtual ~kRenderingEngine(void);
        
        virtual int Configure( const std::string& ConfigFileName );
        virtual int Initialize( const kWinInfo& WinInfo );
        virtual void Finalize();
        
        int OpenSceneModel( const std::string& SceneModelName, int ActiveSceneGraph =0 );
        void CloseSceneModel();
        
        void SetRenderTraverseRoot( const std::vector<kSGNode*>& roots );
        void SetCamera(kCamera& Camera );
        void GetCamera(kCamera& Camera );
        
        void ClearScreen(float r = 0.0f, float g = 0.3f, float b = 0.9f, float a = 0.0f);
        void DoRendering();
        void SwapBuffers();
        
        
    protected:

        kRenderQueueManager*					GetRenderQueueManager()		{return m_pRenderQueueMgr;}
        kCameraManager*							GetCameraManager()			{return m_pCameraMgr;}
        kRenderTargetManager*					GetRenderTargetManager()	{return m_pRenderTargetMgr;}
        kPreRenderManager*						GetPreRenderManager()		{return m_pPreRenderMgr;}
        kGPUResourceManager*				    GetGPUResourceManager()	{return m_pGPUResourceMpr;}
        kRenderPipelineManager*					GetRenderPipelineManager()	{return m_pRenderPipelineMgr;}
        
    protected:
        
        virtual int RegisterPreRenderPrototypes();
        virtual int RegisterRenderPipelinePrototypes();
        
        // user override functions
        virtual int OnConfigure();
        virtual int OnRegisterPreRenderPrototypes();
        virtual int OnRegisterRenderPipelinePrototypes();
        
        virtual void UpdateSynClockMillSecondTime();
        virtual void UpdateFrameIndex();
        
    protected:
        
        kWinInfo								m_WinInfo;
        
        kGPUResourceManager*				    m_pGPUResourceMpr;
        
        kRenderQueueManager*   					m_pRenderQueueMgr;
        kCameraManager*							m_pCameraMgr;

        kRenderTargetManager*					m_pRenderTargetMgr;
        kPreRenderManager*						m_pPreRenderMgr;
        kRenderPipelineManager*					m_pRenderPipelineMgr;

        std::vector<kSGNode*>	                m_TraverseRoots;

        
        IPreRender*								m_pStartPreRender;
        IRenderTarget*						    m_pPrimeTarget;
    };


    const int MAX_FRAMES_IN_FLIGHT = 2;


    class kEngine
    {
    public:
        kEngine() {
            m_pWindow = nullptr;
            currentFrame = 0;
        }

        virtual ~kEngine() {
        }

        void createEngine(GLFWwindow* pwindow);
        void drawFrame();
        void cleanEngine();

        void frameChanged() { framebufferResized = true; }

    protected:
        void createSyncObjects();
        void recreateSwapChain();
        VkExtent2D chooseSwapExtent(GLFWwindow* pwindow, const VkSurfaceCapabilitiesKHR& capabilities);

        void createUniformBuffers(VkDeviceSize bufferSize);
        void updateUniformBuffer(uint32_t currentImage);

        void createCommandBuffers();
        void createDescriptorSets(VkDeviceSize bufferSize);
        void recordCommandBuffer(uint32_t imageIndex);







    protected:

        GLFWwindow* m_pWindow;

        kRHIContext						m_Context;

        kGraphicPipeline				m_GraphicPipeline;

        kRHISwapchain					m_Swapchain;
        kRenderpaas						m_Renderpass;

        VkExtent2D						m_Extent;

        Model							m_Model;

        std::vector<VkDescriptorSet>	descriptorSets;
        std::vector<VkCommandBuffer>	commandBuffers;
        std::vector<kUniformBuffer*>	m_UniformBuffers;

        std::vector<VkSemaphore>		imageAvailableSemaphores;
        std::vector<VkSemaphore>		renderFinishedSemaphores;
        std::vector<VkFence>			inFlightFences;
        uint32_t						currentFrame = 0;

        bool							framebufferResized = false;

    };

}

#endif
