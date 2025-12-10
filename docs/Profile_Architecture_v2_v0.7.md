# 9. Profile Architecture v2

## 9.1 Overview
Profile Architecture v2 defines the canonical model, lifecycle, and runtime binding rules for lightweight identity structures within TL Runtime v0.7. Profiles are deterministic structural entities that support semantic, behavioral, and configuration-level attributes used by the runtime.  

Profiles are distinct from Persona Layer constructs. Profiles are formal, deterministic, and version-bound; Persona Layer (Public Edition) remains stylistic and external to the core runtime.

This chapter establishes the public OSS boundary for Profiles while ensuring full compatibility with UCG, CCMv2, and PCL-v2.

---

## 9.2 Scope and Non-scope

### 9.2.1 Scope
Profile Architecture v2 specifies:
- Canonical Profile Model (CPM-v2)
- Deterministic Profile Lifecycle
- UCG/Identity integration rules
- Runtime binding and execution behavior
- Compatibility rules between profile schema versions

### 9.2.2 Non-scope
Excluded from this chapter:
- Emotional or stylistic behaviors
- Persona-driven adaptation logic
- Private identity models
- Non-deterministic update mechanisms

---

## 9.3 Canonical Profile Model (CPM-v2)

CPM-v2 formalizes Profiles as deterministic bundles that must converge under CCMv2 and remain stable across snapshots.

### 9.3.1 Profile Bundle Structure
A Profile bundle consists of:

**1. ProfileHeader**
- `profile_id`
- `version`
- `canonical_hash`

**2. ProfileBody**
- Canonical semantic/configuration fields
- Optional deterministic extension fields

**3. ProfileFooter**
- `integrity_proof`
- `ucg_projection_signature`

### 9.3.2 Canonical Fields & Deterministic Components
Canonical fields must satisfy:
- Deterministic serialization order  
- Canonical hashing rules  
- Stability under PCL-v2 drift analysis  

### 9.3.3 Profile Type System
Profiles fall into three deterministic categories:
- **Static Profiles** — persistent, stable identity-bound constructs  
- **Dynamic Profiles** — stateful yet deterministic under updates  
- **Ephemeral Profiles** — short-lived, fully deterministic structures  

---

## 9.4 Profile Lifecycle v2

### 9.4.1 Creation — Deterministic Initialization
Profile creation must:
- Use fixed input ordering  
- Establish UCG projection at initialization  
- Converge immediately into canonical form via CCMv2  

### 9.4.2 Evolution — Drift-Aware Updates
Updates occur only when:
- PCL-v2 drift signals justify modification  
- SMM/TIL semantic-temporal constraints remain satisfied  
- Post-update structure preserves CCMv2 consistency  

### 9.4.3 Suspension & Reactivation
A Profile may be suspended when:
- Execution context is detached  
- UCG projection becomes inactive  
- Runtime optimization requests pruning  

Reactivation must follow deterministic re-binding rules.

### 9.4.4 Deprecation Path
A Profile becomes deprecated when:
- Canonical deltas invalidate older schema  
- CVCL mandates structural migration  
- Deterministic guarantees cannot be preserved  

Each profile boundary must respect semantic sealing as defined in SMM-v2, guaranteeing that meaning cannot drift across lifecycle transitions or cross-version activation paths.

---

## 9.5 Profile ⇁EUCG Integration

Profiles operate as identity-bound nodes within the Universal Canonical Graph (UCG).

### 9.5.1 UCG Projection for Profiles
Each Profile must project into UCG with:
- Identity tuple  
- Canonical hash  
- Version bounds  
- Snapshot alignment constraints  

### 9.5.2 Identity-Linked Profiles
These Profiles must:
- Maintain drift stability  
- Preserve referential identity  
- Satisfy UCG invariants  

### 9.5.3 Consistency Rules
Profile-to-UCG consistency holds when:
- Structural drift remains below thresholds  
- Canonical manifold constraints remain satisfiable  
- No conflict arises under PCL-v2 contraction  

---

## 9.6 Runtime Binding & Execution Model

### 9.6.1 Profile Resolution Pipeline
Profiles resolve through:
1. Normalization (CCM)
2. UCG projection
3. Execution-context mapping

### 9.6.2 Dependency Loading Model
Profiles may load:
- Canonical semantic units
- Deterministic configuration modules

Non-deterministic modules are strictly forbidden.

### 9.6.3 Deterministic Execution Context
Execution is allowed only under:
- Stable runtime host conditions  
- Deterministic resource allocation  
- Drift-free temporal windows  

---

## 9.7 Compatibility: v1 → v2 Migration

### 9.7.1 Structural Changes
- Expanded bundle schema  
- Updated canonical hashing behavior  
- Strengthened UCG projection rules  

### 9.7.2 Auto-Migration Rules
The runtime must:
- Detect legacy v1 bundles  
- Normalize → canonicalize → reproject into UCG  
- Enforce drift-safe migration  

### 9.7.3 Backward Compatibility Notes
Legacy Profiles remain readable, but deterministic guarantees may be reduced.

---

## 9.8 Test Guidelines

### 9.8.1 Deterministic Lifecycle Tests
Lifecycle operations must be host-equivalent and snapshot-stable.

### 9.8.2 UCG Integration Tests
Projection must be identical across equivalent runtime states.

### 9.8.3 Drift-Resilience Evaluation
Profile updates must not cause semantic drift beyond defined thresholds.

---
