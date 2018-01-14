$extensions = []
$team = {}

MINIMAL_REQUIREMENTS_BY_DIFFICULTY = [5, 4, 3, 2, 1]


Extension = Struct.new(:name, :difficulty, :allow_multiple, :mutually_exclusive) do
  def to_s
    name.to_s
  end
end


def extension(id, difficulty, allow_multiple: false)
  raise "Multiply defined extension #{id}" if Object.const_defined? id

  extension = Extension.new(id, difficulty, allow_multiple, [])

  Object.const_set(id, extension)
  $extensions << extension
end

def mutually_exclusive(*extensions)
  extensions.each do |x|
    extensions.each do |y|
      x.mutually_exclusive << y
    end
  end
end

class TeamMemberContext
  def initialize(member_id)
    raise "#{member_id} already exists" if $team.has_key? member_id
    
    @member_id = member_id
    $team[member_id] = []
  end
  
  def extension(extension)
    $team[@member_id] << extension
  end
end

def team_member(member_id, &block)
  TeamMemberContext.new(member_id).instance_eval(&block)
end


def check_mutually_exclusive
  $team.each do |id, extensions|
    (0...extensions.size).each do |i|
      (i+1...extensions.size).each do |j|
        x = extensions[i]
        y = extensions[j]

        if x.mutually_exclusive.include? y
          puts "Uh oh! #{id} has made 2 mutually exclusive extensions, namely #{x.name} and #{y.name}"
        end
      end
    end
  end
end

def check_duplicates
  $team.each do |id, extensions|
    (0...extensions.size).each do |i|
      (i+1...extensions.size).each do |j|
        x = extensions[i]
        y = extensions[j]

        if x == y and not x.allow_multiple
          puts "Oh oh! #{id} made #{x.name} multiple times!"
        end
      end
    end
  end

  pairs = $team.to_a

  (0...pairs.size).each do |i|
    (i+1...pairs.size).each do |j|
      id1, ext1 = pairs[i]
      id2, ext2 = pairs[j]

      (0...ext1.size).each do |k|
        (0...ext2.size).each do |n|
          e1 = ext1[k]
          e2 = ext2[n]

          if e1 == e2 and not e1.allow_multiple
            puts "Uh oh! #{id1} and #{id2} have made the same extension #{e1}"
          end
        end
      end
    end
  end
end

def check_difficulties
  $team.each do |id, extensions|
    counts = count_extensions_by_difficulty(extensions)

    (0...counts.size).to_a.reverse.each do |i|
      minimum = MINIMAL_REQUIREMENTS_BY_DIFFICULTY[i]

      if counts[i] < minimum
        puts "Uh oh! #{id} has insufficient extension of difficulty #{i + 1}!"
      else
        counts[i - 1] += counts[i] - minimum
      end
    end
  end
end

def count_extensions_by_difficulty(extensions)
  extension_difficulties = extensions.map(&:difficulty)

  (1..5).map do |difficulty|
    extension_difficulties.count(difficulty)
  end
end

def check_mesh
  $team.each do |id, extensions|
    if not [ MeshReading, MeshOptimizing, MeshRendering ].any? do |e|
         extensions.include? e
       end
      
      puts "Uh oh! #{id} forgot to make a mesh extension (one of MeshReading, MeshOptimizing, MeshRendering)"
    end
  end
end


extension :BasicSample, 1, allow_multiple: true
extension :BasicScripting, 1, allow_multiple: true
extension :RayTracerV1, 1, allow_multiple: true
extension :RayTracerV2, 2
extension :RayTracerV3, 2
extension :RayTracerV4, 2
extension :RayTracerV5, 3
extension :RayTracerV6, 4
extension :RandomSampler, 2
extension :StratifiedSampler, 2
extension :JitteredSampler, 2
extension :HalfJitteredSampler, 2
extension :NRooksSampler, 3
extension :MultijitteredSampler, 4
extension :DepthOfFieldCamera, 3
extension :FisheyeCamera, 4
extension :OrthographicCamera, 4
extension :DirectionalLight, 2
extension :SpotLight, 3
extension :AreaLight, 2
extension :Voronoi2D, 5
extension :Voronoi3D, 5
extension :MaterialDalmatian2D, 5
extension :MaterialVerticalLines, 2
extension :MaterialGrid2d, 2
extension :MaterialCheckered2D, 2
extension :MaterialDalmatian3D, 5
extension :MaterialGrid3d, 2
extension :MaterialCheckered3D, 2
extension :MaterialWorley2D, 3
extension :MaterialWorley3D, 3
extension :MaterialPerlin2D, 5
extension :MaterialPerlin3D, 5
extension :MaterialMarble2D, 3
extension :MaterialMarble3D, 3
extension :MaterialTransformer2D, 3
extension :MaterialTransformer3D, 3
extension :MaterialScale2D, 3
extension :MaterialScale3D, 3
extension :MaterialTranslate2D, 3
extension :MaterialTranslate3D, 3
extension :MaterialRotate2D, 3
extension :MaterialRotate3D, 3
extension :PlaneXZ, 1
extension :PlaneYZ, 1
extension :PlaneXZOptimized, 1
extension :PlaneYZOptimized, 1
extension :ConeAlongX, 3
extension :ConeAlongY, 3
extension :ConeAlongZ, 3
extension :ConeAlongXOptimized, 2
extension :ConeAlongYOptimized, 2
extension :ConeAlongZOptimized, 2
extension :SquareXY, 1
extension :SquareXZ, 1
extension :SquareYZ, 1
extension :SquareXYOptimized, 1
extension :SquareXZOptimized, 1
extension :SquareYZOptimized, 1
extension :Cube, 2
extension :CylinderAlongX, 2
extension :CylinderAlongY, 2
extension :CylinderAlongZ, 2
extension :CylinderAlongXOptimized, 1
extension :CylinderAlongYOptimized, 1
extension :CylinderAlongZOptimized, 1
extension :Triangle, 2
extension :TriangleOptimized, 1
extension :BoundingBox, 2
extension :Cropper, 3
extension :CropperOptimized, 2
extension :Bumpifier, 5
extension :Intersection, 5
extension :IntersectionOptimized, 2
extension :Difference, 5
extension :DifferenceOptimized, 2
extension :PrimitiveScaling, 1
extension :PrimitiveRotationX, 1
extension :PrimitiveRotationY, 1
extension :PrimitiveRotationZ, 1
extension :Group, 2
extension :Edge, 5
extension :Cartoon, 3
extension :ParallelScheduler, 4, allow_multiple: true
extension :MotionBlur, 4
extension :Bmp, 2
extension :Ppm, 3
extension :EasingLibrary, 2
extension :Bounce, 3
extension :Elastic, 3
extension :Quadratic, 4
extension :Cubic, 4
extension :Quintic,4 
extension :PointAnimation, 2
extension :AngleAnimation, 2
extension :Quaternions, 2
extension :CircularAnimation, 2
extension :Lissajous, 4
extension :Cyclic, 3
extension :Slicer, 3
extension :MeshReading, 5
extension :MeshOptimizing, 5
extension :MeshRendering, 5

mutually_exclusive Bounce, Elastic
mutually_exclusive PlaneXZ, PlaneYZ
mutually_exclusive PlaneXZOptimized, PlaneYZOptimized
mutually_exclusive ConeAlongX, ConeAlongY, ConeAlongZ
mutually_exclusive ConeAlongXOptimized, ConeAlongYOptimized, ConeAlongZOptimized
mutually_exclusive SquareXY, SquareXZ, SquareYZ
mutually_exclusive SquareXYOptimized, SquareXZOptimized, SquareYZOptimized
mutually_exclusive CylinderAlongX, CylinderAlongY, CylinderAlongZ
mutually_exclusive CylinderAlongXOptimized, CylinderAlongYOptimized, CylinderAlongZOptimized
mutually_exclusive PrimitiveRotationX, PrimitiveRotationY, PrimitiveRotationZ
mutually_exclusive MaterialScale2D, MaterialTranslate2D, MaterialRotate2D
mutually_exclusive MaterialScale3D, MaterialTranslate3D, MaterialRotate3D
mutually_exclusive Quadratic, Cubic, Quintic
mutually_exclusive PointAnimation, AngleAnimation

load 'team-data.rb'

puts "*** Warning: this script is not finished yet!"

check_mutually_exclusive
check_duplicates
check_difficulties
check_mesh

# print_statistics
