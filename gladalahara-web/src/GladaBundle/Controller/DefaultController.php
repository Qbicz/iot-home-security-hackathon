<?php

namespace GladaBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Method;
use GladaBundle\Entity\Result;
use GladaBundle\Entity\Alarm;

class DefaultController extends Controller
{
    /**
     * @Route("/",name="main")
     * @Method("GET")
     */
    public function indexAction()
    {
      $em = $this->getDoctrine()->getManager();
      $settings = $em->getRepository('GladaBundle:Setting')->findAll();
      $alarmon = $settings[5]->getValue();
      $light1on = $settings[6]->getValue();
      $light2on = $settings[7]->getValue();
      $acon = $settings[8]->getValue();
        return $this->render('GladaBundle:Default:index.html.twig',array('last'=>$this->getLastResults(),'aon'=>$alarmon,'l1on'=>$light1on,'l2on'=>$light2on,'acon'=>$acon));
    }
    /**
    * @Route("/getlastresults")
    */
    public function getLastResultsAction(){
      return new JsonResponse($this->getLastResults());
    }
    /**
    * @Route("/confirm")
    */
    public function confirmAction(){
      $em = $this->getDoctrine()->getManager();
      $alarms = $em->getRepository('GladaBundle:Alarm')->findBy(array('seen'=>0));
      foreach($alarms as $alarm){
        $alarm->setSeen(1);
      }
      $em->flush();
      return new JsonResponse(1);
    }
    /**
    * @Route("/settings/save")
    * @Method("POST")
    */
    public function saveSettingsAction(Request $request){
      $em = $this->getDoctrine()->getManager();
      $settings = $em->getRepository('GladaBundle:Setting')->findAll();
      $settings[0]->setValue($request->get("mail"));
      $settings[1]->setValue($request->get("pir"));
      $settings[2]->setValue($request->get("window"));
      $settings[3]->setValue($request->get("temp1"));
      $settings[4]->setValue($request->get("temp2"));
      $em->flush();
      return new JsonResponse(1);
    }
    /**
    * @Route("/data/send")
    * @Method("POST")
    */
    public function dataSendAction(Request $request){
      if($request->get('room') && $request->get('data')){
        $roomid = $request->get('room');
        $data = explode(',',$request->get('data'));
        $em = $this->getDoctrine()->getManager();
        $sensors = $em->getRepository('GladaBundle:Sensor')->findBy(array('room'=>$roomid));
        $res = new Result();
        $res->setTime(new \DateTime("now"));
        $res->setSensor($sensors[1]);
        $res->setValue($data[1]);
        $em->persist($res);
        $settings = $em->getRepository('GladaBundle:Setting')->findAll();
        $pid = $settings[1]->getValue();
        $window = $settings[2]->getValue();
        $temp1 = $settings[3]->getValue();
        $temp2 = $settings[4]->getValue();
        $alarmon = $settings[5]->getValue();
        if($alarmon && ($data[0]==1 && (($roomid==1 && $pid[0]=="1") || ($roomid==2 && $window[0]=="1") ))){
          $alarm = new Alarm();
          $alarm->setTime(new \DateTime("now"));
          $alarm->setSensor($sensors[0]);
          $alarm->setSeen(0);
          $em->persist($alarm);
        }
        $em->flush();
        return new Response($this->getRightResponse());
      }
      return new Response(chr(0));
    }
    /**
    * @Route("/test")
    */
    public function getRightResponseAction(){
      //setting 0->alarm,1->mail,2->lights,3->wentylator
      $em = $this->getDoctrine()->getManager();
      $settings = $em->getRepository('GladaBundle:Setting')->findAll();
      $pid = $settings[1]->getValue();
      $window = $settings[2]->getValue();
      $temp1 = $settings[3]->getValue();
      $temp2 = $settings[4]->getValue();
      $alarmon = $settings[5]->getValue();
      $light1on = $settings[6]->getValue();
      $light2on = $settings[7]->getValue();
      $acon = $settings[8]->getValue();

      $lastRes = $this->getLastResults();
      $alarm = ($pid[0]&&$lastRes[0][3])||($window[0]&&$lastRes[2][3])&&$alarmon;
      $light1 = $light1on||($pid[2]&&$lastRes[0][3])||($window[2]&&$lastRes[2][3])||($temp1[2]&&($lastRes[1][3]>26||$lastRes[1][3]<18))||($temp2[2]&&($lastRes[3][3]>26||$lastRes[3][3]<18));
      $light2 = $light2on||($pid[2]&&$lastRes[0][3])||($window[2]&&$lastRes[2][3])||($temp1[2]&&($lastRes[1][3]>26||$lastRes[1][3]<18))||($temp2[2]&&($lastRes[3][3]>26||$lastRes[3][3]<18));
      $ac = $acon||($pid[3]&&$lastRes[0][3])||($window[3]&&$lastRes[2][3])||($temp1[3]&&($lastRes[1][3]>26||$lastRes[1][3]<18))||($temp2[3]&&($lastRes[3][3]>26||$lastRes[3][3]<18));
      $r = $ac*16+$alarm*4+$light2*2+$light1;
      return new JsonResponse(array($alarm,$light1,$light2,$ac));
    }
    /**
    * @Route("/update/setting/{id}/{val}")
    */
    public function updateSetting($id,$val){
      $em = $this->getDoctrine()->getManager();
      $settings = $em->getRepository('GladaBundle:Setting')->find($id);
      $settings->setValue($val);
      $em->flush();
      return new JsonResponse(1);
    }
    public function getRightResponse(){
      //setting 0->alarm,1->mail,2->lights,3->wentylator
      $em = $this->getDoctrine()->getManager();
      $settings = $em->getRepository('GladaBundle:Setting')->findAll();
      $pid = $settings[1]->getValue();
      $window = $settings[2]->getValue();
      $temp1 = $settings[3]->getValue();
      $temp2 = $settings[4]->getValue();
      $alarmon = $settings[5]->getValue();
      $light1on = $settings[6]->getValue();
      $light2on = $settings[7]->getValue();
      $acon = $settings[8]->getValue();

      $lastRes = $this->getLastResults();
      $alarm = ($pid[0]&&$lastRes[0][3])||($window[0]&&$lastRes[2][3])&&$alarmon;
      $light1 = $light1on||($pid[2]&&$lastRes[0][3])||($window[2]&&$lastRes[2][3])||($temp1[2]&&($lastRes[1][3]>26||$lastRes[1][3]<18))||($temp2[2]&&($lastRes[3][3]>26||$lastRes[3][3]<18));
      $light2 = $light2on||($pid[2]&&$lastRes[0][3])||($window[2]&&$lastRes[2][3])||($temp1[2]&&($lastRes[1][3]>26||$lastRes[1][3]<18))||($temp2[2]&&($lastRes[3][3]>26||$lastRes[3][3]<18));
      $ac = $acon||($pid[3]&&$lastRes[0][3])||($window[3]&&$lastRes[2][3])||($temp1[3]&&($lastRes[1][3]>26||$lastRes[1][3]<18))||($temp2[3]&&($lastRes[3][3]>26||$lastRes[3][3]<18));
      $r = $ac*16+$alarm*4+$light2*2+$light1;
      return chr($r);
    }
    /**
    * @Route("/settings",name="settings")
    */
    public function settingsAction(){
      $em = $this->getDoctrine()->getManager();
      $settings = $em->getRepository('GladaBundle:Setting')->findAll();
      $res = array();
      foreach($settings as $setting){
        $res[$setting->getName()] = $setting->getValue();
      }
      return $this->render('GladaBundle:Default:settings.html.twig',array('settings'=>$res));
    }
    public function getLastResults(){
      $em = $this->getDoctrine()->getManager();
      $sensors = $em->getRepository('GladaBundle:Sensor')->findBy(array(),array('room'=>"ASC"));
      $json = Array();
      foreach($sensors as $sensor){
        $res = $em->getRepository('GladaBundle:Result')->findOneBy(array('sensor'=>$sensor),array('id'=>'DESC'));
        $res = ($res)?$res->getValue():null;
        if(!$res){
          $res = $em->getRepository('GladaBundle:Alarm')->findOneBy(array('sensor'=>$sensor,'seen'=>0),array('id'=>'DESC'));
          $res = ($res)?1:0;
        }
        $json[] = Array($sensor->getName(),$sensor->getRoom(),$sensor->getType(),$res);
      }
      return $json;
    }
}
